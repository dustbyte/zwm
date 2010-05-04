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
// ZDisplay.hpp for project zwm
//
// Made by mota
// email <mota@souitom.net>
//
// Started on  Tue May  4 11:07:49 2010 mota
// Last update Tue May  4 11:15:33 2010 pierre wacrenier
//

#include <string>

#include <X11/Xlib.h>

namespace ZX
{
  class ZDisplay
  {
  private:
    static ZDisplay * _instance;
    Display * _dpy;
    std::string _name;

    ZDisplay(const std::string & name);
    ZDisplay(const ZDisplay &); // undefined
    ZDisplay(void);
    virtual ~ZDisplay();

    static void		destroyInstance(void);

  public:
    bool		isOpen(void) const;
    static ZDisplay *	getInstance(void);
    static ZDisplay *	getInstance(const std::string & name);
  };
}
