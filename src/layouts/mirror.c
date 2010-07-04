#include <stdlib.h>
#include <stdio.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"

void		layout_mirror(Wm *wm)
{
  Workspace	*cur = &wm->workspaces[wm->cwrksp];
  t_list	*clients = &cur->windows;
  t_elem	*tmp;
  Client	*client;
  unsigned int	win_width;
  unsigned int	win_width_master;
  unsigned int	left_num;
  unsigned int	right_num;
  Bool		left = True;
  unsigned int	yleft;
  unsigned int	yright;
  unsigned int	left_height;
  unsigned int	right_height;

  if (clients->size == 1)
    {
      move_resize_window(wm, clients->head->data,
			 0, wm->bar_height,
			 wm->scr_width - 2, wm->scr_height - 2);
    }
  else if (clients->size == 2)
    {
      win_width = wm->scr_width * cur->master_width;
      move_resize_window(wm, clients->head->data,
			 0, wm->bar_height,
			 win_width - 2, wm->scr_height - 2);
      move_resize_window(wm, clients->tail->data,
			 win_width, wm->bar_height,
			 wm->scr_width - win_width - 2, wm->scr_height - 2);
    }
  else if (clients->size >= 3)
    {
      win_width_master = wm->scr_width * cur->master_width;
      win_width = (wm->scr_width - win_width_master) / 2;
      right_num = (clients->size - 1) / 2;
      left_num = clients->size - 1 - right_num;
      yleft = wm->bar_height;
      yright = wm->bar_height;
      left_height = wm->scr_height / left_num;
      right_height = wm->scr_height / right_num;
      list_foreach_as(clients->head, tmp, (Client *), client)
	{
	  if (tmp == clients->head)
	    {
	      move_resize_window(wm, client,
				 win_width, wm->bar_height,
				 win_width_master - 2,
				 wm->scr_height - 2);
	    }
	  else
	    {
	      if (left)
		{
		  move_resize_window(wm, client,
				     0, yleft,
				     win_width - 2,
				     left_height - 2);
		  yleft += left_height;
		}
	      else
	      	{
	      	  move_resize_window(wm, client,
				     win_width + wm->scr_width - (2 * win_width),
				     yright,
				     win_width - 2,
				     right_height - 2);
	      	  yright += right_height;
	      	}
	      left = !left;
	    }
	}
    }
}
