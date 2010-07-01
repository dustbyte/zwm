#include "zwm.h"

extern Wm	wm;

void		resize(const Arg *arg)
{
  if ((arg->dval > 0 && wm.conf->master_width + arg->dval <= 1.0) ||
      (arg->dval < 0 && wm.conf->master_width + arg->dval >= 0.0))
    wm.conf->master_width += arg->dval;
  draw(&wm);
}
