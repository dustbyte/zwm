#include <iostream>
#include <string>
#include <cstdlib>

#include <X11/Xlib.h>

#include "Display.hpp"

namespace ZX
{

  Display*	Display::_instance = NULL;

  Display::Display(void) :
    _dpy(NULL),
    _name()
  {
    _dpy = XOpenDisplay(NULL);
    _screen = DefaultScreen(_dpy);
  }

  Display::Display(const std::string & name) :
    _dpy(NULL),
    _name(name)
  {
    _dpy = XOpenDisplay(_name.c_str());
    _screen = DefaultScreen(_dpy);
  }

  Display::~Display()
  {
    if (_dpy != NULL)
      XCloseDisplay(_dpy);
  }

  void		Display::destroyInstance(void)
  {
    if (Display::_instance != NULL)
      {
	delete Display::_instance;
      }
  }

  Display &	Display::getInstance(void)
  {
    if (Display::_instance == NULL)
      {
	Display::_instance = new Display;
	::atexit(Display::destroyInstance);
      }
    return (*(Display::_instance));
  }

  Display &	Display::getInstance(const std::string & name)
  {
    if (Display::_instance == NULL)
      {
	Display::_instance = new Display(name);
	::atexit(Display::destroyInstance);
      }
    return (*(Display::_instance));
  }

  bool			Display::isOpen(void) const
  {
    return (_dpy != NULL);
  }

  ::Display *		Display::getDisplay(void) const
  {
    return (_dpy);
  }

  std::string		Display::getName(void) const
  {
    return (_name);
  }

  int			Display::getScreen(void) const
  {
    return (_screen);
  }

}
