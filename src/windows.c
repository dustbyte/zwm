#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"
#include "tools.h"

Client		*add_window(Wm *wm, Window window)
{
  Client	*win;
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  if ((win = malloc(sizeof(*win))) == NULL)
    wlog(SYS | ERR, "malloc");
  win->win = window;
  list_add_head(&cur->windows, &win->self, win);
  cur->focus = cur->windows.head->data;
  return (win);
}

void		remove_window(Wm *wm, Client *win)
{
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  if (win == cur->focus)
    {
      if (win->self.next != NULL)
	cur->focus = win->self.next->data;
      else if (win->self.prev != NULL)
	cur->focus = win->self.prev->data;
      else
	cur->focus = NULL;
    }
  list_delete(&cur->windows, &win->self, list_free_dfl);
  if (cur->windows.size == 0)
    cur->focus = NULL;
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

void		set_win_attributes(Client *client,
				   unsigned int x, unsigned int y,
				   unsigned int width, unsigned int height,
				   unsigned int border_width)
{
  client->x = x;
  client->y = y;
  client->width = width;
  client->height = height;
  client->border_width = border_width;
}

void		move_resize_window(Wm *wm, Client *client,
				   unsigned int x, unsigned int y,
				   unsigned int width, unsigned int height)
{
  set_win_attributes(client, x, y, width, height, client->border_width);
  base_move_resize_window(wm, client);
}

void		base_move_resize_window(Wm *wm, Client *client)
{
  XMoveResizeWindow(wm->dpy, client->win,
		    client->x,
		    client->y,
		    client->width,
		    client->height);
}

void		border_width_window(Wm *wm, Client *client, unsigned int width)
{
  client->border_width = width;
  XSetWindowBorderWidth(wm->dpy, client->win, width);
}
