#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

void		layout_monocle(Wm *wm)
{
  Workspace	*cur = &wm->workspaces[wm->cwrksp];

  if (cur->focus != NULL)
    {
      XMoveResizeWindow(wm->dpy, cur->focus->win, 0, 0,
			wm->scr_width - 2, wm->scr_height - 2);
    }
}
