#include <cstdarg>
#include <cstdio>

#include "Log.hpp"

namespace ZX
{

  Log::Log(void) :
    mLevel(DEBUG)
  {}

  Log::Log(const int level) :
    mLevel(level)
  {}

  Log::~Log(void)
  {}

  void		Log::setLevel(const int level)
  {
    mLevel = level;
  }

  int		Log::getLevel(void) const
  {
    return (mLevel);
  }

  int		Log::raw_log(FILE * stream, const char * const fmt, va_list * ap) const
  {
    char *	buf;
    int		rt;

    rt = vasprintf(&buf, fmt, *ap);
    fprintf(stream, buf);
    return (rt);
  }

  int		Log::debug(const char * const fmt, ...) const
  {
    va_list	ap;
    int		rt;

    if (mLevel <= DEBUG)
      {
	va_start(ap, fmt);
	rt = raw_log(stdout, fmt, &ap);
	va_end(ap);    
	return (rt);
      }
    return (0);
  }

  int		Log::warning(const char * const fmt, ...) const
  {
    va_list	ap;
    int		rt;

    if (mLevel <= WARNING)
      {
	va_start(ap, fmt);
	rt = raw_log(stderr, fmt, &ap);
	va_end(ap);    
	return (rt);
      }
    return (0);    
  }

}
