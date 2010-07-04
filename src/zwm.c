#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "lists.h"
#include "log.h"
#include "zwm.h"
#include "tools.h"
#include "config.h"

/*
** Globals
*/

Wm		wm;

static void	(*handlers[LASTEvent])(Wm *wm, XEvent *event) =
{
  [KeyPress] = key_press,
  [MapRequest] = map_request,
  [DestroyNotify] = destroy_notify,
  [EnterNotify] = enter_notify,
  /* [ButtonPress] = button_press, */
  [ConfigureRequest] = configure_request,
  [ConfigureNotify] = configure_notify
};

void		draw(Wm *wm)
{
  t_elem	*tmp;
  Client	*client;
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  layouts[cur->layout].func(wm);
  list_foreach_as(cur->windows.head, tmp, (Client *), client)
    {
      if (client == cur->focus)
	{
	  XSetWindowBorderWidth(wm->dpy, client->win, 1);
	  XSetWindowBorder(wm->dpy, client->win, wm->colors.focus);
	  XSetInputFocus(wm->dpy,client->win,RevertToParent,CurrentTime);
	  XRaiseWindow(wm->dpy,client->win);
	}
      else
	XSetWindowBorder(wm->dpy, client->win, wm->colors.unfocus);
    }
}

void		undraw(Wm *wm)
{
  Workspace	*cur = &wm->workspaces[wm->cwrksp];
  t_elem	*tmp;
  Client	*client;

  list_foreach_as(cur->windows.head, tmp, (Client *), client)
    XUnmapWindow(wm->dpy, client->win);
}

void		redraw(Wm *wm)
{
  Workspace	*cur = &wm->workspaces[wm->cwrksp];
  t_elem	*tmp;
  Client	*client;

  list_foreach_as(cur->windows.head, tmp, (Client *), client)
    XMapWindow(wm->dpy, client->win);
  draw(wm);
}

void		key_press(Wm *wm, XEvent *event)
{
  unsigned	i;
  KeySym	keysym;
  XKeyEvent	keyevent;

  keyevent = event->xkey;
  keysym = XKeycodeToKeysym(wm->dpy, keyevent.keycode, 0);

  for (i = 0; i < TABLELENGTH(keys); ++i)
    if (keys[i].keysym == keysym && keys[i].mod == keyevent.state)
      keys[i].func(&keys[i].arg);
}

/* void		button_press(Wm *wm, XEvent *event) */
/* { */
/*   t_elem	*tmp; */
/*   Client	*client; */
/*   Window	event_win; */
/*   Workspace	*cur = &wm->workspaces[wm->cwrksp]; */

/*   event_win = event->xbutton.subwindow; */
/*   printf("Window button pressed = %d\n", (int) event_win); */
/*   list_foreach_as(cur->windows.head, tmp, (Client *), client) */
/*     { */
/*       if (client->win == event_win) */
/* 	{ */
/* 	  cur->focus = client; */
/* 	  draw(wm); */
/* 	  break; */
/* 	} */
/*     } */
/* } */

void		enter_notify(Wm *wm, XEvent *event)
{
  t_elem	*tmp;
  Client	*client;
  Workspace	*cur = &wm->workspaces[wm->cwrksp];
  XCrossingEvent	enter_event;

  if (FOCUS_FOLLOWS_MOUSE == true)
    {
      enter_event = event->xcrossing;
      list_foreach_as(cur->windows.head, tmp, (Client *), client)
	{
	  if (client->win == enter_event.window)
	    {
	      cur->focus = client;
	      draw(wm);
	      break;
	    }
	}
    }
}

void		map_request(Wm *wm, XEvent *event)
{
  printf("Window map request %d\n", (int) event->xmaprequest.window);
  add_window(wm, event->xmaprequest.window);
  XMapWindow(wm->dpy, event->xmaprequest.window);
  XSelectInput(wm->dpy, event->xmaprequest.window, EnterWindowMask);
  draw(wm);
}

void		destroy_notify(Wm *wm, XEvent *event)
{
  Client	*win;

  if ((win = get_window(wm, event->xdestroywindow.window)) != NULL)
    {
      remove_window(wm, win);
      XSync(wm->dpy, False);
      draw(wm);
    }
}

void		configure(Wm *wm, Client *c)
{
  XConfigureEvent ce;
  XWindowAttributes attr;

  if (!XGetWindowAttributes(wm->dpy, c->win, &attr))
    {
      ce.type = ConfigureNotify;
      ce.display = wm->dpy;
      ce.event = c->win;
      ce.window = c->win;
      ce.x = attr.x;
      ce.y = attr.y;
      ce.width = attr.width;
      ce.height = attr.height;
      ce.border_width = attr.border_width;
      ce.above = None;
      ce.override_redirect = False;
      XSendEvent(wm->dpy, c->win, False, StructureNotifyMask, (XEvent *)&ce);
    }
}

void		configure_request(Wm *wm, XEvent *event)
{
  Client	*c;
  XConfigureRequestEvent *ev = &event->xconfigurerequest;
  XWindowChanges wc;

  if (!(c = get_window(wm, ev->window)))
    {
      wc.x = ev->x;
      wc.y = ev->y;
      wc.width = ev->width;
      wc.height = ev->height;
      wc.border_width = ev->border_width;
      wc.sibling = ev->above;
      wc.stack_mode = ev->detail;
      XConfigureWindow(wm->dpy, ev->window, ev->value_mask, &wc);
    }
  else
    configure(wm, c);
  XSync(wm->dpy, False);
}

void		configure_notify(Wm *wm, XEvent *event)
{
  wlog(RUN | INFO, "Configure Notify");
  (void)wm;
  (void)event;
}

void		run_wm(Wm *wm)
{
  XEvent	event;

  while (wm->is_running && !XNextEvent(wm->dpy, &event))
    {
      if (handlers[event.type])
	handlers[event.type](wm, &event);
    }
}

void		grab_keys(Wm *wm)
{
  size_t	i;
  KeyCode	code;

  for (i = 0; i < TABLELENGTH(keys); i++)
    {
      if ((code = XKeysymToKeycode(wm->dpy, keys[i].keysym)))
	XGrabKey(wm->dpy, code, keys[i].mod, wm->root, True, GrabModeAsync, GrabModeAsync);
    }
}

void		free_client(void *elem)
{
  Client	*client = (Client *)elem;

  XKillClient(wm.dpy, client->win);
  free(client);
}

void		finish_wm(Wm *wm)
{
  size_t	i;

  for (i = 0; i < TABLELENGTH(workspaces); i++)
    list_empty(&wm->workspaces[i].windows, free_client);
  XCloseDisplay(wm->dpy);
}

void sigchld(__attribute__((unused))int unused) {
  if(signal(SIGCHLD, sigchld) == SIG_ERR)
    wlog(SYS|ERR, "Can't install SIGCHLD handler");
  while(0 < waitpid(-1, NULL, WNOHANG));
}

void		init_wm(Wm *wm)
{
  XSetWindowAttributes wa;

  sigchld(0);
  wm->is_running = true;
  wm->cwrksp = 0;
  wm->workspaces = workspaces;
  if ((wm->dpy = XOpenDisplay(NULL)) == NULL)
    wlog(XLIB | ERR, "Cannot open display");
  else
    wlog(XLIB | INFO, "Display Opened");
  wm->screen = DefaultScreen(wm->dpy);
  wm->root = RootWindow(wm->dpy, wm->screen);
  wm->bar_height = BAR_HEIGHT;
  wm->scr_width = DisplayWidth(wm->dpy, wm->screen);
  wm->scr_height = DisplayHeight(wm->dpy, wm->screen) - wm->bar_height;
  wm->colors.focus = get_color(FOCUS_COLOR, wm);
  wm->colors.unfocus = get_color(UNFOCUS_COLOR, wm);
  wm->layouts_number = TABLELENGTH(layouts);
  wm->layouts = layouts;
  wm->zmenu.status = ZMENU_NORMAL;
  bzero(wm->zmenu.buf, 4096);
  wm->zmenu.exec_list = NULL;
  grab_keys(wm);
  wa.event_mask = SubstructureNotifyMask|SubstructureRedirectMask;
  XChangeWindowAttributes(wm->dpy, wm->root, CWEventMask, &wa);
  XSelectInput(wm->dpy, wm->root, wa.event_mask);
}

int		main(void)
{
  init_wm(&wm);
  run_wm(&wm);
  finish_wm(&wm);
  return (0);
}
