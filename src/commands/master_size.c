#include "zwm.h"

extern Wm	wm;

void		master_size(const Arg *arg)
{
  unsigned int	max;
  unsigned int	*master_size;

  max = wm.workspaces[wm.cwrksp].windows.size;
  master_size = &wm.workspaces[wm.cwrksp].master_size;
  if ((arg->val > 0 && *master_size + arg->val <= max) ||
      (arg->val < 0 && *master_size + arg->val > 0))
    *master_size += arg->val;
  draw(&wm);
}
