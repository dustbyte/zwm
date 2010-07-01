#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		kill_client(__attribute__((unused))const Arg *arg)
{
  Workspace	*cur = &wm.workspaces[wm.cwrksp];
  t_list	*clients = &cur->windows;
  Client	*focus = cur->focus;

  if (focus != NULL)
    {
      if (focus->self.next != NULL)
	cur->focus = focus->self.next->data;
      else if (clients->size > 0)
	cur->focus = clients->head->data;
      XKillClient(wm.dpy, focus->win);
      remove_window(&wm, focus);
      draw(&wm);
    }
}
