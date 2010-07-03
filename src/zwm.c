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
  [ConfigureNotify] = configure_notify,
  [EnterNotify] = enter_notify
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

void		enter_notify(Wm *wm, XEvent *event)
{
  t_elem	*tmp;
  Client	*client;
  Workspace	*cur = &wm->workspaces[wm->cwrksp];
  XCrossingEvent	enter_event;

  enter_event = event->xcrossing;
  printf("EntrerNotify -> %d\n", enter_event.window);
  list_foreach_as(cur->windows.head, tmp, (Client *), client)
    {
      if (client->win == enter_event.window)
	{
	  cur->focus = client;
	  break;
	}
    }
  draw(wm);
}

void		map_request(Wm *wm, XEvent *event)
{
  add_window(wm, event->xmaprequest.window);
  XMapWindow(wm->dpy, event->xmaprequest.window);
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

void		configure_notify(Wm *wm, XEvent *event)
{
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
  wa.event_mask = SubstructureNotifyMask|SubstructureRedirectMask|EnterWindowMask;
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
