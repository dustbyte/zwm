#ifndef		LOG_H_
# define	LOG_H_

/*
** t_log gl_log
*/

#define		LOGBSIZE	1024
#define		PROGNAME	"zwm"

/*
** Il faut juste eviter les collisions entre e_loglvl et e_logtype
*/

typedef enum		e_loglvl
{
  INFO = 0x4,
  WARN = 0x2,
  ERR = 0x1
}			t_loglvl;

typedef enum		e_logtype
{
  SYS = 0x100,
  NET = 0x200,
  XLIB = 0x400,
  RUN = 0x800
}			t_logtype;

typedef struct		s_log
{
  FILE			*log_out;
  FILE			*log_err;
  unsigned int		max_log_lvl;
}			t_log;

typedef struct		s_err_format
{
  const unsigned short	type;
  const unsigned short	err;
  const char		*str;
  FILE			**output;
}			t_err_format;

typedef struct		s_err_type
{
  const unsigned int	type;
  const char		*str;
}			t_err_type;

# define	DFL_LOG_LVL	INFO

# define	ERR_FORMAT_MAX	(sizeof(err_format) / sizeof(*err_format))
# define	ERR_FORMAT_DEFAULT	1
# define	ERR_TYPE_MAX	(sizeof(err_type) / sizeof(*err_type))
# define	ERR_TYPE_DEFAULT	0

int		wlog(t_loglvl lvl, const char *str, ...);
void		*wlog_p(t_loglvl lvl, const char *str, ...);

#endif		/* !LOG_H_ */
