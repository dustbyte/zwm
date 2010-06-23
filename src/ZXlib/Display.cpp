//
// Copyright(c), zwm
// All rights reserved.
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of the University of California, Berkeley nor the
//       names of its contributors may be used to endorse or promote products
//       derived from this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Display.cpp for project zwm
// 
// Made by mota
// email <mota@souitom.net>
// 
// Started on  Wed Jun 23 17:20:35 2010 mota
// Last update Wed Jun 23 17:20:36 2010 pierre wacrenier
//

#include <iostream>
#include <string>
#include <cstdlib>

#include <X11/Xlib.h>

#include "ZDisplay.hpp"

namespace ZX
{

  Display*	Display::_instance = NULL;

  Display::Display(void) :
    _dpy(NULL),
    _name()
  {
    _dpy = XOpenDisplay(NULL);
  }

  Display::Display(const std::string & name) :
    _dpy(NULL),
    _name(name)
  {
    _dpy = XOpenDisplay(_name.c_str());
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
}
