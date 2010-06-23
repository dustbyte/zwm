
#include <iostream>

#include "ZDisplay.hpp"

int			main(void)
{
  ZX::Display &		dpy = ZX::Display::getInstance();
  std::string		name;

  if (dpy.isOpen() && dpy.getName().size() > 0)
    {
      std::cout << "name = " << dpy.getName() << std::endl;
    }
  return (0);
}
