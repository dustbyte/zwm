
#include <iostream>

#include "ZDisplay.hpp"

int		main(void)
{
  ZX::ZDisplay	*dpy;
  std::string	name;

  dpy = ZX::ZDisplay::getInstance();
  if (dpy->isOpen() && dpy->getName().size() > 0)
    {
      std::cout << "name = " << dpy->getName() << std::endl;
    }
  return (0);
}
