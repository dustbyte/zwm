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

  printf("%d %d\n", client->width, client->height);
}

void		move_to_workspace(const Arg *arg)
{
  unsigned int	wrksp = arg->val;
  Workspace	*cur = &wm.workspaces[wm.cwrksp];
  Workspace	*new = &wm.workspaces[wrksp];
  Client	*focus = cur->focus;

  if (focus)
    {
      printf("\ncur = %p || new = %p\n\n", cur, new);

      printf("Before");
      if (cur->windows.head != NULL)
	show_client(cur->windows.head->data);
      list_show(&cur->windows, show_client);

      list_remove(&cur->windows, &focus->self);

      printf("\nAfter");
      if (cur->windows.head != NULL)
	show_client(cur->windows.head->data);
      list_show(&cur->windows, show_client);

      unmap_window(&wm, focus);
      if (cur->windows.size > 0)
	cur->focus = (Client *)cur->windows.head->data;
      else
	cur->focus = NULL;
      list_add_head(&new->windows, &focus->self, focus->self.data);

      printf("\nNew");
      if (new->windows.head != NULL)
	show_client(new->windows.head->data);
      list_show(&new->windows, show_client);

      new->focus = focus;
      redraw(&wm);
    }
}
