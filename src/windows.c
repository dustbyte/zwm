#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"
#include "tools.h"

void		add_window(Wm *wm, Window window)
{
  Client	*win;

  if ((win = malloc(sizeof(*win))) == NULL)
    wlog(SYS | ERR, "malloc");
  win->win = window;
  list_add_head(&wm->workspaces[wm->cwrksp].windows, &win->self, win);
  wm->workspaces[wm->cwrksp].focus = wm->workspaces[wm->cwrksp].windows.head->data;
}

void		remove_window(Wm *wm, Client *win)
{
  if (win == wm->workspaces[wm->cwrksp].focus)
    {
      if (win->self.next != NULL)
	wm->workspaces[wm->cwrksp].focus = win->self.next->data;
      else if (win->self.prev != NULL)
	wm->workspaces[wm->cwrksp].focus = win->self.prev->data;
      else
	wm->workspaces[wm->cwrksp].focus = NULL;
    }
  list_delete(&wm->workspaces[wm->cwrksp].windows, &win->self, list_free_dfl);
}

Client		*get_window(Wm *wm, Window window)
{
  t_elem	*tmp;
  Client	*win;

  list_foreach_as(wm->workspaces[wm->cwrksp].windows.head, tmp, (Client *), win)
    if (win->win == window)
      return (win);
  return (NULL);
}
