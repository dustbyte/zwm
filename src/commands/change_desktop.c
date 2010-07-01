#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		change_desktop(const Arg *arg)
{
  unsigned int	desk = arg->val;

  wlog(RUN | INFO, "Current workspace = %d || wanted workspace = %d", wm.cwrksp, desk);
  undraw(&wm);
  wm.cwrksp = desk;
  redraw(&wm);
}
