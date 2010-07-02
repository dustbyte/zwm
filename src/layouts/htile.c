#include <stdlib.h>

#include "lists.h"
#include "zwm.h"

void		layout_htile(Wm *wm)
{
  unsigned int	i;
  unsigned int	x;
  unsigned int	y;
  unsigned int	win_height;
  unsigned int	win_width;
  t_elem	*tmp;
  Client	*client;
  Workspace	*cwrksp;
  unsigned int	num_master;

  cwrksp = &wm->workspaces[wm->cwrksp];
  num_master = cwrksp->windows.size <= cwrksp->master_size ?
    cwrksp->windows.size : cwrksp->master_size;
  if (num_master && cwrksp->windows.size <= cwrksp->master_size)
    {
      x = 0;
      win_width = wm->scr_width / cwrksp->windows.size;
      list_foreach_as(cwrksp->windows.head, tmp, (Client *), client)
	{
	  XMoveResizeWindow(wm->dpy, client->win, x, wm->bar_height,
			    win_width - 2, wm->scr_height - 2);
	  x += win_width;
	}
    }
  else if (num_master)
    {
      i = 0;
      x = 0;
      win_width = wm->scr_width / num_master;
      win_height = wm->scr_height * wm->workspaces[wm->cwrksp].master_width;
      list_foreach_as(cwrksp->windows.head, tmp, (Client *), client)
	{
	  if (i < num_master)
	    {
	      XMoveResizeWindow(wm->dpy, client->win, x, wm->bar_height,
				win_width - 2, win_height - 2);
	    }
	  else
	    {
	      if (i == num_master)
		{
		  x = 0;
		  y = wm->bar_height + win_height;
		  win_height = wm->scr_height - win_height;
		  win_width = wm->scr_width / (cwrksp->windows.size - num_master);
		}
	      XMoveResizeWindow(wm->dpy, client->win, x, y,
				win_width - 2, win_height - 2);
	    }
	  x += win_width;
	  ++i;
	}
    }
}
