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
  int		y = (zm->conf->top == true) ? 0 : zm->scr_height - zm->conf->height;

  wa.override_redirect = True;
  wa.background_pixmap = ParentRelative;
  wa.event_mask = ExposureMask | ButtonPressMask | KeyPressMask | VisibilityChangeMask;
  zm->win = XCreateWindow(zm->dpy, zm->root,
			  zm->conf->x, y, zm->conf->width, zm->conf->height, 0,
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

void		draw_menu(ZMenu *zm)
{
  Dims		dims, cpy;
  t_elem	*tmp;
  Item		*item;

  dims.x = zm->conf->x;
  dims.y = (zm->conf->top == true) ? 0 : zm->scr_height - zm->conf->height;
  dims.width = zm->conf->width;
  dims.height = zm->conf->height;
  cpy = dims;
  dims.x += draw_text(zm, &zm->dconf.n, &dims, NULL);
  draw_text(zm, &zm->dconf.n, &dims, zm->buf);
  dims.x = zm->max + zm->conf->space;
  if (zm->selected)
    {
      dims.x += draw_text(zm, &zm->dconf.s, &dims, zm->selected->name);
      list_foreach_as(zm->selected->self.next, tmp, (Item *), item)
	{
	  if (dims.x > zm->conf->width - zm->conf->x - text_width(zm, item->name))
	    break ;
	  dims.x += draw_text(zm, &zm->dconf.n, &dims, item->name);
	}
    }
  XCopyArea(zm->dpy, zm->dw, zm->win, zm->dconf.gc,
	    cpy.x, cpy.y, cpy.width, cpy.height, 0, 0);
}

int		draw_text(ZMenu *zm, Color *color, Dims *dims, char *str)
{
  size_t	len;
  int		x, y, h;
  XRectangle	rec = { dims->x, dims->y, dims->width, dims->height};

  h = zm->dconf.font_info->ascent + zm->dconf.font_info->descent;
  if (str)
    rec.width = text_width(zm, str) + h;
  XSetForeground(zm->dpy, zm->dconf.gc, color->bg);
  XFillRectangles(zm->dpy, zm->dw, zm->dconf.gc, &rec, 1);
  if (!str)
    return (0);
  len = strlen(str);
  y = dims->y + ((h + 2) / 2) + zm->dconf.font_info->ascent;
  x = dims->x + (h / 2);
  XSetForeground(zm->dpy, zm->dconf.gc, color->fg);
  XDrawString(zm->dpy, zm->dw, zm->dconf.gc, x, y, str, len);
  return (rec.width);
}

void		finish(ZMenu *zm)
{
  if (zm->selected != NULL)
    {
      printf("%s", zm->selected->name);
      fflush(stdout);
    }
  list_empty(&zm->items, item_free);
  XFreeGC(zm->dpy, zm->dconf.gc);
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
  return (c.pixel);}

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
      if (zm->selected && zm->selected->self.next != NULL)
	zm->selected = zm->selected->self.next->data;
      break ;
    case XK_Left:
      if (zm->selected && zm->selected->self.prev != NULL)
	zm->selected = zm->selected->self.prev->data;
      break ;
    default:
      break ;
    }
  draw_menu(zm);
  if (zm->selected)
    item_show(zm->selected);
}

void		read_stdin(ZMenu *zm)
{
  char		buf[BUFSIZE];
  size_t	len;
  size_t	xlen;
  Item		*item;

  while (fgets(buf, BUFSIZE, stdin) != NULL)
    {
      len = strlen(buf);
      if (buf[len - 1] == '\n')
	buf[--len] = '\0';
      if (!len)
	return ;
      xlen = text_width(zm, buf);
      zm->max = xlen > zm->max ? xlen : zm->max;
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
	case Expose:
	  if (ev.xexpose.count == 0)
	    draw_menu(zm);
	  break ;
	case KeyPress:
	  key_press(zm, &ev.xkey);
	case VisibilityNotify:
	  if (ev.xvisibility.state != VisibilityUnobscured)
	    XRaiseWindow(zm->dpy, zm->win);
	default:
	  break ;
	}
    }
}

void		setup(ZMenu *zm, Conf *conf)
{
  zm->is_running = true;
  zm->selected = NULL;
  zm->max = 0;
  zm->conf = conf;
  zm->cmp = zm->conf->icase == true ? strncasecmp : strncmp;
  memset(zm->buf, 0, BUFSIZE);
  list_init(&zm->items);
  list_init(&zm->match);

  if ((zm->dpy = XOpenDisplay(NULL)) == NULL)
    die("Cannot open display");
  zm->screen = DefaultScreen(zm->dpy);
  zm->root = RootWindow(zm->dpy, zm->screen);
  zm->scr_width = DisplayWidth(zm->dpy, zm->screen);
  zm->scr_height = DisplayHeight(zm->dpy, zm->screen);
  if (zm->conf->width == 0)
    zm->conf->width = zm->scr_width - zm->conf->x;
  if (zm->conf->height == 0)
    zm->conf->height = DFL_HEIGHT;

  create_widow(zm);
  zm->dw = XCreatePixmap(zm->dpy, zm->root,
			 zm->conf->width, zm->conf->height,
			 DefaultDepth(zm->dpy, zm->screen));
  zm->dconf.n.bg = get_color(zm, conf->n_bgcolor);
  zm->dconf.n.fg = get_color(zm, conf->n_fgcolor);
  zm->dconf.s.bg = get_color(zm, conf->s_bgcolor);
  zm->dconf.s.fg = get_color(zm, conf->s_fgcolor);
  zm->dconf.gc = create_gc(zm, zm->dconf.n.bg, zm->dconf.n.fg);
  if ((zm->dconf.font_info = XLoadQueryFont(zm->dpy, conf->font)) == NULL
      && (zm->dconf.font_info = XLoadQueryFont(zm->dpy, "fixed")) == NULL)
    die("Cannot load font ``%s''\n", conf->font);

  read_stdin(zm);
  grab_keyboard(zm);
  XMapRaised(zm->dpy, zm->win);
}

void		setup_conf(int ac, char **av, Conf *conf)
{
  int		i;

  for (i = 1; i < ac; i++)
    {
      if (!strcmp(av[i], "-i"))
	conf->icase = true;
      else if (!strcmp(av[i], "-b"))
	conf->top = False;
      else if (!strcmp(av[i], "-x") && (++i < ac))
	conf->x = atoi(av[i]);
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

int		text_width(ZMenu *zm, char *str)
{
  return (XTextWidth(zm->dconf.font_info, str, strlen(str)));
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
