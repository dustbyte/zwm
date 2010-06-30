#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"
#include "config.h"

void		finish_wm(Wm *wm)
{
  XCloseDisplay(wm->dpy);
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
}

int		main(void)
{
  Wm		wm;

  init_wm(&wm);
  finish_wm(&wm);
  return (0);
}
