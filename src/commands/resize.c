#include "zwm.h"

extern Wm	wm;

void		resize(const Arg *arg)
{
  double	*master_width;

  master_width = &wm.workspaces[wm.cwrksp].master_width;
  if ((arg->dval > 0 && *master_width + arg->dval <= 1.0) ||
      (arg->dval < 0 && *master_width + arg->dval >= 0.0))
    *master_width += arg->dval;
  draw(&wm);
}
