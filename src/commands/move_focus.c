#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		move_focus(const Arg *arg)
{
  int		val = arg->val;
  Workspace	*cur= &wm.workspaces[wm.cwrksp];
  t_list	*clients = &cur->windows;

  if (clients->size > 0)
    {
      if (val < 0)
	{
	  if (cur->focus->self.prev != NULL)
	    cur->focus = cur->focus->self.prev->data;
	  else
	    cur->focus = clients->tail->data;
	}
      else if (val > 0)
	{
	  if (cur->focus->self.next != NULL)
	    cur->focus = cur->focus->self.next->data;
	  else
	    cur->focus = clients->head->data;
	}
    }
  draw(&wm);
}
