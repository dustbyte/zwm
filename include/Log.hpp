#ifndef LOG_HPP_
#define LOG_HPP_

#include <cstdarg>

namespace ZX
{

  enum			LOGLEVEL
    {
      ERROR = 0,
      WARNING = 1,
      DEBUG = 2
    };

  class Log
  {
  private:
    int			mLevel;
    int			raw_log(FILE * stream, const char * const fmt, va_list * ap) const;

  public:
    Log(void);
    Log(const int level);
    Log(const Log &);				// not implemented

    Log			operator=(const Log &); // not implemented

    virtual ~Log(void);

    void		setLevel(const int level);
    int			getLevel(void) const;
    int			debug(const char * const fmt, ...) const;
    int			warning(const char * const fmt, ...) const;
    int			error(const char * const fmt, ...) const;
  };

}

#endif		// LOG_HPP_
