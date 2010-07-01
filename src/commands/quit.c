#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		quit(__attribute__((unused)) const Arg *arg)
{
  wm.is_running = false;
}
