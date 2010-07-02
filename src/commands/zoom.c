#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		zoom(__attribute__((unused))const Arg *arg)
{
  Workspace	*cur = &wm.workspaces[wm.cwrksp];
  t_list	*clients = &cur->windows;

  if (clients->size > 1)
    {
      if (&cur->focus->self != clients->head)
	{
	  list_remove(clients, &cur->focus->self);
	  list_add_head(clients, &cur->focus->self, cur->focus->self.data);
	}
      else
	list_swap_next(clients, clients->head);
    }
  draw(&wm);
}
