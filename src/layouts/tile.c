#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"

void		layout_tile(Wm *wm)
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
    cwrksp->windows.size : cwrksp->windows.size - (cwrksp->windows.size - cwrksp->master_size);
  wlog(RUN | INFO, "WIN NBR = %d || NUM MASTER = %d", cwrksp->windows.size, num_master);
  if (num_master && cwrksp->windows.size <= cwrksp->master_size)
    {
      y = 0;
      win_height = wm->scr_height / num_master;
      list_foreach_as(cwrksp->windows.head, tmp, (Client *), client)
	{
	  XMoveResizeWindow(wm->dpy, cwrksp->focus->win, 0, y,
			    wm->scr_width - 2, win_height - 2);
	  y += win_height;
	}
    }
  else if (num_master)
    {
      i = 1;
      y = 0;
      win_height = wm->scr_height / num_master;
      win_width = wm->scr_width * wm->conf->master_width;
      wlog(RUN|INFO, "WIN WIDTH = %d", win_width);
      list_foreach_as(cwrksp->windows.head, tmp, (Client *), client)
	{
	  if (i <= num_master)
	    {
	      XMoveResizeWindow(wm->dpy, cwrksp->focus->win, 0, y,
				win_width - 2, win_height - 2);
	    }
	  else
	    {
	      if (i == num_master + 1)
		{
		  x = win_width;
		  y = 0;
		  win_height = wm->scr_height / (cwrksp->windows.size - num_master);
		  win_width = wm->scr_width - win_width;
		}
	      XMoveResizeWindow(wm->dpy, cwrksp->focus->win, x, y,
				win_width - 2, win_height - 2);
	    }
	  y += win_height;
	  ++i;
	}
    }
}
