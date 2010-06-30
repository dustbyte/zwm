#include <stdlib.h>
#include <stdio.h>

#include	"log.h"
#include	"zwm.h"

void		spawn(const Arg *arg)
{
  (void)arg;
  wlog(RUN | INFO, "SPAWN");
}
