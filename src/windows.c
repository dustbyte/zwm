#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <X11/Xlib.h>
#include <X11/Xproto.h>
#include <X11/Xutil.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"

Client		*add_window(Wm *wm, Window window)
{
  Client	*win;
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  if ((win = malloc(sizeof(*win))) == NULL)
    wlog(SYS | ERR, "malloc");
  win->win = window;
  win->mapped = false;
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
  map_window(wm, client);
  set_win_attributes(client, x, y, width, height, client->border_width);
  base_move_resize_window(wm, client);
}

void		map_window(Wm *wm, Client *client)
{
  if (!client->mapped)
    {
      XMapWindow(wm->dpy, client->win);
      client->mapped = true;
    }
}

void		unmap_window(Wm *wm, Client *client)
{
  if (client->mapped)
    {
      XUnmapWindow(wm->dpy, client->win);
      client->mapped = false;
    }
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

unsigned int	check_rules(Wm *wm, Window win)
{
  size_t	i;
  XClassHint	class_hint;
  unsigned int	wrkspc = wm->cwrksp;

  if (wm->rules_nb <= 0 || !XGetClassHint(wm->dpy, win, &class_hint))
    return (wm->cwrksp);
  for (i = 0; i < wm->rules_nb; i++)
    {
      if (!strncmp(class_hint.res_class, wm->rules[i].class,
		   strlen(class_hint.res_class)))
	{
	  wrkspc = wm->rules[i].workspace;
	  break ;
	}
    }
  XFree(class_hint.res_name);
  XFree(class_hint.res_class);
  return (wrkspc);
}
