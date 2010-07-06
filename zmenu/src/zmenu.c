#include <unistd.h>

#include <stdarg.h>

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>


#include "lists.h"

#include "zmenu.h"
#include "config.h"

GC		create_gc(ZMenu *zm, unsigned int bg, unsigned int fg)
{
  XGCValues	values;
  unsigned long	value_mask = GCForeground | GCBackground;

  values.foreground = fg;
  values.background = bg;
  return (XCreateGC(zm->dpy, zm->win, value_mask, &values));
}

void		create_widow(ZMenu *zm)
{
  XSetWindowAttributes wa;

  wa.override_redirect = True;
  wa.background_pixmap = ParentRelative;
  wa.event_mask = ExposureMask | ButtonPressMask | KeyPressMask | VisibilityChangeMask;
  zm->win = XCreateWindow(zm->dpy, zm->root,
			  zm->conf->x, zm->conf->y, zm->conf->width, zm->conf->height, 0,
			  DefaultDepth(zm->dpy, zm->screen), CopyFromParent,
			  DefaultVisual(zm->dpy, zm->screen),
			  CWOverrideRedirect | CWBackPixmap | CWEventMask, &wa);
}

void		die(const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  exit(EXIT_FAILURE);
}

void		finish(ZMenu *zm)
{
  if (zm->selected != NULL)
    {
      printf("%s", zm->selected->name);
      fflush(stdout);
    }
  list_empty(&zm->items, item_free);
  XFreeGC(zm->dpy, zm->dconf.normal);
  XFreeGC(zm->dpy, zm->dconf.selected);
  XFreeFont(zm->dpy, zm->dconf.font_info);
  XUngrabKeyboard(zm->dpy, CurrentTime);
  XDestroyWindow(zm->dpy, zm->win);
  XCloseDisplay(zm->dpy);
}

unsigned long	get_color(ZMenu *zm, const char *color)
{
  XColor	c;
  Colormap	map;

  map = DefaultColormap(zm->dpy, zm->screen);
  if (!XAllocNamedColor(zm->dpy, map, color, &c, &c))
    die(PROGNAME"-"VERSION" cannot alloc color %s\n", color);
  return (c.pixel);
}

void		grab_keyboard(ZMenu *zm)
{
  size_t	len;

  for(len = 1000; len; len--)
    if(XGrabKeyboard(zm->dpy, zm->root, True,
		     GrabModeAsync, GrabModeAsync, CurrentTime) == GrabSuccess)
      return ;
  usleep(1000);
  die("Cannot grab keyboard\n");
}

int		item_cmp(void *item1, void *item2)
{
  Item		*i1 = item1, *i2 = item2;

  return (strcmp(i2->name, i1->name));
}

void		item_free(void *it)
{
  Item		*item = it;

  free(item->name);
  free(item);
}

void		item_show(void *it)
{
  Item		*item = it;

  printf("name = %s\n", item->name);
}

void		key_press(ZMenu *zm, XKeyEvent *key)
{
  KeySym	key_sym;

  key_sym = XKeycodeToKeysym(zm->dpy, key->keycode, 0);
  switch (key_sym)
    {
    case XK_Escape:
      zm->is_running = false;
      zm->selected = NULL;
      break;
    case XK_Return:
      zm->is_running = false;
      break ;
    case XK_Right:
      if (zm->selected->self.next != NULL)
	zm->selected = zm->selected->self.next->data;
      break ;
    case XK_Left:
      if (zm->selected->self.prev != NULL)
	zm->selected = zm->selected->self.prev->data;
      break ;
    default:
      break ;
    }
  if (zm->selected)
    item_show(zm->selected);
}

void		read_stdin(ZMenu *zm)
{
  char		buf[BUFSIZE];
  size_t	len;
  Item		*item;

  list_init(&zm->items);
  while (fgets(buf, BUFSIZE, stdin) != NULL)
    {
      len = strlen(buf);
      zm->max = len > zm->max ? len : zm->max;
      if (buf[len - 1] == '\n')
	buf[len - 1] = '\0';
      if ((item = malloc(sizeof(*item))) == NULL)
	die("malloc");
      if ((item->name = strdup(buf)) == NULL)
	die("strdup");
      list_insert(&zm->items, &item->self, item, item_cmp);
    }
  zm->selected = zm->items.head->data;
}

void		run(ZMenu *zm)
{
  XEvent	ev;

  while (zm->is_running && !XNextEvent(zm->dpy, &ev))
    {
      switch (ev.type)
	{
	case KeyPress:
	  key_press(zm, &ev.xkey);
	default:
	  break ;
	}
    }
}

void		setup(ZMenu *zm, Conf *conf)
{
  int		scr_width;
  int		scr_height;

  zm->is_running = true;
  zm->selected = NULL;
  zm->max = 0;
  zm->conf = conf;
  if (zm->conf->width == 0)
    zm->conf->width = scr_width - zm->conf->x;
  if (zm->conf->height == 0)
    zm->conf->height = 20;
  if ((zm->dpy = XOpenDisplay(NULL)) == NULL)
    die("Cannot open display");
  zm->screen = DefaultScreen(zm->dpy);
  zm->root = RootWindow(zm->dpy, zm->screen);
  create_widow(zm);
  zm->dconf.normal = create_gc(zm,
				get_color(zm, conf->n_bgcolor),
				get_color(zm, conf->n_fgcolor));
  zm->dconf.selected = create_gc(zm,
				get_color(zm, conf->s_bgcolor),
				get_color(zm, conf->s_fgcolor));
  if ((zm->dconf.font_info = XLoadQueryFont(zm->dpy, conf->font)) == NULL
      && (zm->dconf.font_info = XLoadQueryFont(zm->dpy, "fixed")) == NULL)
    die("Cannot load font ``%s''\n", conf->font);
  read_stdin(zm);
  scr_width = DisplayWidth(zm->dpy, zm->root);
  scr_height = DisplayHeight(zm->dpy, zm->root);
  XMapRaised(zm->dpy, zm->win);
  grab_keyboard(zm);
}

void		setup_conf(int ac, char **av, Conf *conf)
{
  int		i;

  for (i = 1; i < ac; i++)
    {
      if (!strcmp(av[i], "-i"))
	conf->cmp = strncasecmp;
      else if (!strcmp(av[i], "-b"))
	conf->top = False;
      else if (!strcmp(av[i], "-x") && (++i < ac))
	conf->x = atoi(av[i]);
      else if (!strcmp(av[i], "-y") && (++i < ac))
	conf->y = atoi(av[i]);
      else if (!strcmp(av[i], "-width") && (++i < ac))
	conf->width = atoi(av[i]);
      else if (!strcmp(av[i], "-height") && (++i < ac))
	conf->height = atoi(av[i]);
      else if (!strcmp(av[i], "-font") && (++i < ac))
	conf->font = av[i];
      else if (!strcmp(av[i], "-nb") && (++i < ac))
	conf->n_bgcolor = av[i];
      else if (!strcmp(av[i], "-nf") && (++i < ac))
	conf->n_fgcolor = av[i];
      else if (!strcmp(av[i], "-sb") && (++i < ac))
	conf->s_bgcolor = av[i];
      else if (!strcmp(av[i], "-sf") && (++i < ac))
	conf->s_fgcolor = av[i];
    }
}

void		usage(void)
{
  die("usage: "PROGNAME" [-i] [-b]\
 [-x posx] [-y posy] [-width val] [-height val]\
 [-font fontname] [-nb color] [-nf color] [-sb color] [-sf color]\n");
}

int		main(int ac, char **av)
{
  ZMenu		zm;

  setup_conf(ac, av, &conf);
  setup(&zm, &conf);
  run(&zm);
  finish(&zm);
  return (EXIT_SUCCESS);
}
