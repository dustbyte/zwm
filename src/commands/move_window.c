#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "lists.h"
#include "zwm.h"

extern Wm	wm;

void		move_window(const Arg *arg)
{
  int		val = arg->val;
  Workspace	*cur = &wm.workspaces[wm.cwrksp];
  t_list	*clients = &cur->windows;

  if (clients->size > 1)
    {
      if (val > 0)
	list_swap_next(clients, &cur->focus->self);
      else if (val < 0)
	list_swap_prev(clients, &cur->focus->self);
    }
  draw(&wm);
}
