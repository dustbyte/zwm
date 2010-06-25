#include <iostream>
#include <string>
#include <cstdlib>

#include <X11/Xlib.h>

#include "Display.hpp"

namespace ZX
{

  Display*		Display::mInstance = NULL;

  Display::Display(void) :
    mDpy(NULL),
    mName()
  {
    mDpy = XOpenDisplay(NULL);
    mScreen = DefaultScreen(mDpy);
  }

  Display::Display(const std::string & name) :
    mDpy(NULL),
    mName(name)
  {
    mDpy = XOpenDisplay(mName.c_str());
    mScreen = DefaultScreen(mDpy);
  }

  Display::~Display()
  {
    if (mDpy != NULL)
      XCloseDisplay(mDpy);
  }

  void			Display::destroyInstance(void)
  {
    if (Display::mInstance != NULL)
      {
	delete Display::mInstance;
      }
  }

  Display &	Display::getInstance(void)
  {
    if (Display::mInstance == NULL)
      {
	Display::mInstance = new Display;
	::atexit(Display::destroyInstance);
      }
    return (*(Display::mInstance));
  }

  Display &		Display::getInstance(const std::string & name)
  {
    if (Display::mInstance == NULL)
      {
	Display::mInstance = new Display(name);
	::atexit(Display::destroyInstance);
      }
    return (*(Display::mInstance));
  }

  bool			Display::isOpen(void) const
  {
    return (mDpy != NULL);
  }

  ::Display *		Display::getDisplay(void) const
  {
    return (mDpy);
  }

  std::string		Display::getName(void) const
  {
    return (mName);
  }

  int			Display::getScreen(void) const
  {
    return (mScreen);
  }

}
