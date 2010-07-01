#include "zwm.h"

void		layout_tile(Wm *wm)
{
  int		master_width;
  Workspace	*c_workspace;

  workspace = &wm->workspaces[cwrksp];
  if (c_workspace->windows.size == 1)
    {
      XMoveResizeWindow(wm->dpy, c_workspace->focus->win, 0, 0,c);
    }
}
