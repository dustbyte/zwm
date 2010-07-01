#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "log.h"
#include "zwm.h"

extern Wm	wm;

void		spawn(const Arg *arg)
{
  pid_t		pid;

  if ((pid = fork()) == 0)
    {
      if (wm.dpy != NULL)
	close(ConnectionNumber(wm.dpy));
      setsid();
      execvp(((char **) arg->args)[0], (char **) arg->args);
      wlog(SYS | ERR, "can't start %s", ((char **) arg->args)[0]);
      exit(0);
    }
  else if (pid < 0)
    wlog(SYS | ERR, "fork failed, can't start %s", ((char **) arg->args)[0]);
}

void		quit(__attribute__((unused)) const Arg *arg)
{
  wm.is_running = false;
}
