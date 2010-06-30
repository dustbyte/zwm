#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"
#include "tools.h"

void		add_window(Wm *wm, Window window)
{
  ZWindow	*win;

  if ((win = malloc(sizeof(*win))) == NULL)
    wlog(SYS | ERR, "malloc");
  win->win = window;
  list_add_head(&wm->cur_workspace->windows, &win->self, win);
}
