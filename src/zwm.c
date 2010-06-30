#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"
#include "config.h"

/*
** Globals
*/

Wm		wm;

static void	(*handlers[LASTEvent])(Wm *wm, XEvent *event) =
{
  [KeyPress] = NULL,
  [MapRequest] = map_request,
  [DestroyNotify] = NULL,
  [ConfigureNotify] = NULL
};

void		tile(Wm *wm)
{
  (void)wm;
}

void		map_request(Wm *wm, XEvent *event)
{
  add_window(wm, event->xmaprequest.window);
  XMapWindow(wm->dpy, event->xmaprequest.window);
  tile(wm);
}

void		run_wm(Wm *wm)
{
  XEvent	event;

  while (wm->is_running && !XNextEvent(wm->dpy, &event))
    if (handlers[event.type])
      handlers[event.type](wm, &event);
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

void		finish_wm(Wm *wm)
{
  XCloseDisplay(wm->dpy);
}

void		init_wm(Wm *wm)
{
  wm->is_running = true;
  wm->cur_workspace = 0;
  wm->workspaces = workspaces;
  wm->conf = &conf;
  if ((wm->dpy = XOpenDisplay(NULL)) == NULL)
    wlog(XLIB | ERR, "Cannot open display");
  else
    wlog(XLIB | INFO, "Display Opened");
  wm->screen = DefaultScreen(wm->dpy);
  wm->root = RootWindow(wm->dpy, wm->screen);
  grab_keys(wm);
}

int		main(void)
{
  init_wm(&wm);
  run_wm(&wm);
  finish_wm(&wm);
  return (0);
}
