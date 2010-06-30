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
  list_add_head(&wm->cur_workspace->windows, &win->self, win);
  wm->cur_workspace->focus = wm->cur_workspace->windows.head->data;
}

void		remove_window(Wm *wm, Client *win)
{
  if (win == wm->cur_workspace->focus)
    {
      if (win->self.next != NULL)
	wm->cur_workspace->focus = win->self.next->data;
      else if (win->self.prev != NULL)
	wm->cur_workspace->focus = win->self.prev->data;
      else
	wm->cur_workspace->focus = NULL;
    }
  list_delete(&wm->cur_workspace->windows, &win->self, list_free_dfl);
}

Client		*get_window(Wm *wm, Window window)
{
  t_elem	*tmp;
  Client	*win;

  list_foreach_as(wm->cur_workspace->windows.head, tmp, (Client *), win)
    if (win->win == window)
      return (win);
  return (NULL);
}
