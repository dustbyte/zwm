#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		change_workspace(const Arg *arg)
{
  unsigned int	wrksp = arg->val;

  undraw(&wm);
  wm.cwrksp = wrksp;
  draw(&wm);
}

void		show_client(void *c)
{
  Client	*client = c;

  printf("%d %d :: %d\n", client->width, client->height, client->mapped);
}

void		move_to_workspace(const Arg *arg)
{
  unsigned int	wrksp = arg->val;
  Workspace	*cur = &wm.workspaces[wm.cwrksp];
  Workspace	*new = &wm.workspaces[wrksp];
  Client	*focus = cur->focus;
  t_elem	*elem;

  if (focus && new != cur)
    {
      elem = list_remove(&cur->windows, &focus->self);
      if (cur->windows.size > 0)
	cur->focus = (Client *)cur->windows.head->data;
      else
	cur->focus = NULL;
      unmap_window(&wm, focus);
      list_add_head(&new->windows, elem, elem->data);
      new->focus = focus;
      draw(&wm);
    }
}
