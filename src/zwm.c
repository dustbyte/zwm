#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

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
  /* [ConfigureNotify] = NULL */
};

void		draw(Wm *wm)
{
  t_elem	*tmp;
  Client	*client;
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  wlog(RUN | WARN, "DRAW");
  cur->layout->func(wm);
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

void		print_window(void *win)
{
  Client	*window = (Client *)win;

  printf("Win = %d\n", (int)window->win);
}

void		map_request(Wm *wm, XEvent *event)
{
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  wlog(RUN | WARN, "MAPREQUEST");
  add_window(wm, event->xmaprequest.window);
  list_show(&cur->windows, print_window);
  XMapWindow(wm->dpy, event->xmaprequest.window);
  draw(wm);
}

void		destroy_notify(Wm *wm, XEvent *event)
{
  Client	*win;

  if ((win = get_window(wm, event->xdestroywindow.window)) != NULL)
    {
      remove_window(wm, win);
      draw(wm);
    }
}

void		run_wm(Wm *wm)
{
  XEvent	event;

  while (wm->is_running && !XNextEvent(wm->dpy, &event))
    if (handlers[event.type])
      handlers[event.type](wm, &event);
  XSync(wm->dpy, False);
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
  XSync(wm->dpy, False);
}

void		finish_wm(Wm *wm)
{
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
  wm->conf = &conf;
  if ((wm->dpy = XOpenDisplay(NULL)) == NULL)
    wlog(XLIB | ERR, "Cannot open display");
  else
    wlog(XLIB | INFO, "Display Opened");
  wm->screen = DefaultScreen(wm->dpy);
  wm->root = RootWindow(wm->dpy, wm->screen);
  wm->scr_width = DisplayWidth(wm->dpy, wm->screen);
  wm->scr_height = DisplayHeight(wm->dpy, wm->screen);
  wm->colors.focus = get_color(conf.border_focus, wm);
  wm->colors.unfocus = get_color(conf.border_unfocus, wm);
  grab_keys(wm);
  wa.event_mask = SubstructureNotifyMask|SubstructureRedirectMask;
  XChangeWindowAttributes(wm->dpy, wm->root, CWEventMask, &wa);
  XSelectInput(wm->dpy, wm->root, wa.event_mask);
  XSync(wm->dpy, False);
}

int		main(void)
{
  init_wm(&wm);
  run_wm(&wm);
  finish_wm(&wm);
  return (0);
}
