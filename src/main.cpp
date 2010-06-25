
#include <iostream>

#include "Display.hpp"
#include "Log.hpp"

int			main(void)
{
  ZX::Display &		dpy = ZX::Display::getInstance();
  ZX::Log		log;

  if (dpy.isOpen())
    log.debug("display open\n");
  return (0);
}
