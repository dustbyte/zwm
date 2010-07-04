#include "zwm.h"

extern Wm	wm;

void		zmenu_run(const Arg *arg)
{
  (void)arg;
  wm.zmenu.status = ZMENU_CALL;
}
