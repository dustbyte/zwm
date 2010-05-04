
#include <iostream>

#include "ZDisplay.hpp"

int		main(void)
{
  ZX::ZDisplay	*dpy;

  dpy = ZX::ZDisplay::getInstance();
  std::cout << dpy->isOpen() << std::endl;
  return (0);
}
