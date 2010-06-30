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

static void	(*handlers[LASTEvent])(XEvent *event) =
{
  [KeyPress] = NULL,
  [MapRequest] = NULL,
  [DestroyNotify] = NULL,
  [ConfigureNotify] = NULL
};

void		finish_wm(Wm *wm)
{
  XCloseDisplay(wm->dpy);
}

void		run_wm(Wm *wm)
{
  XEvent	event;

  while (wm->is_running && !XNextEvent(wm->dpy, &event))
    if (handlers[event.type])
      handlers[event.type](&event);
}

void		init_wm(Wm *wm)
{
  wm->cur_workspace = 0;
  wm->workspaces = workspaces;
  wm->conf = &conf;
  if ((wm->dpy = XOpenDisplay(NULL)) == NULL)
    wlog(XLIB | ERR, "Cannot open display");
  else
    wlog(XLIB | INFO, "Display Opened");
  wm->screen = DefaultScreen(wm->dpy);
  wm->root = RootWindow(wm->dpy, wm->screen);
}

int		main(void)
{
  init_wm(&wm);
  finish_wm(&wm);
  return (0);
}
