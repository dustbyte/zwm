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

void		remove_window(Wm *wm, Window window)
{
  t_elem	*tmp;
  ZWindow	*win;

  list_foreach_as(wm->cur_workspace->windows.head, tmp, (ZWindow *), win)
    {
      if (win->win == window)
	break;
    }
  if (tmp != NULL)
    list_delete(&wm->cur_workspace->windows, tmp, list_free_dfl);
}
