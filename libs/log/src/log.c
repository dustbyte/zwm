#include <errno.h>
#include <stdarg.h>

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "log.h"

t_log		gl_log =
{
  NULL,
  NULL,
  DFL_LOG_LVL
};

static const t_err_format	err_format[] =
{
  {ERR,		1, "error", 	&gl_log.log_err	},
  {WARN,	0, "warning",	&gl_log.log_err	},
  {INFO,	0, "info",	&gl_log.log_out	}
};

static const t_err_type		err_type[] =
{
  {SYS,		"system"	},
  {NET,		"network"	},
  {XLIB,	"Xlib"		},
  {RUN,		"run"		}
};

static void	init(void)
{
  static short	flushtime = 10;

  if (gl_log.log_out == NULL)
    gl_log.log_out = stdout;
  if (gl_log.log_err == NULL)
    gl_log.log_err = stderr;
  if (flushtime-- <= 0)
    {
      fflush(gl_log.log_out);
      fflush(gl_log.log_err);
      flushtime = 10;
    }
}

static void	raw_log(t_loglvl lvl, const char *fmt, va_list ap)
{
  unsigned int	f;
  unsigned int	t;
  FILE		*output;

  init();
  for (f = 0; (f < ERR_FORMAT_MAX); f++)
    if (err_format[f].type & lvl)
      break;
  if (f == ERR_FORMAT_MAX)
    f = ERR_FORMAT_DEFAULT;
  if (err_format[f].type <= gl_log.max_log_lvl)
    {
      for (t = 0; (t < ERR_TYPE_MAX); t++)
	if (err_type[t].type & lvl)
	  break;
      if (t == ERR_TYPE_MAX)
	t = ERR_TYPE_DEFAULT;
      output = *(err_format[f].output);
      fprintf(output, "%s: %s: %s: ",
	  PROGNAME, err_format[f].str, err_type[t].str);
      vfprintf(output, fmt, ap);
      if (err_format[f].err == 1)
	fprintf(output, " (%s)", strerror(errno));
      fprintf(output, "\n");
    }
}

int		wlog(t_loglvl lvl, const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  raw_log(lvl, fmt, ap);
  va_end(ap);
  if (lvl & ERR)
    exit(EXIT_FAILURE);
  else if (lvl & WARN)
    return (-1);
  return (0);
}

void		*wlog_p(t_loglvl lvl, const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  raw_log(lvl, fmt, ap);
  va_end(ap);
  return ((void *)NULL);
}
