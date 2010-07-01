#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		switch_layout(const Arg *arg)
{
  int		val = arg->val;
  Workspace	*cur= &wm.workspaces[wm.cwrksp];

  if (val < 0)
    {
      if (cur->layout > 0)
	--cur->layout;
      else
	cur->layout = wm.layouts_number - 1;
    }
  else if (val > 0)
    {
      if (cur->layout < wm.layouts_number - 1)
	++cur->layout;
      else
	cur->layout = 0;
    }
  draw(&wm);
}
