#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"
#include "tools.h"

unsigned long	ZGetColor(const char *color, Wm *wm)
{
  XColor	c;
  Colormap	map;

  map = DefaultColormap(wm->dpy, wm->screen);
  if (!XAllocNamedColor(wm->dpy, map, color, &c, &c))
    wlog(XLIB | ERR, "Bad color %s", color);
  return (c.pixel);
}
