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
// Dislpay.hpp for project zwm
//
// Made by mota
// email <mota@souitom.net>
//
// Started on  Wed Jun 23 17:21:00 2010 mota
// Last update Wed Jun 23 17:21:02 2010 pierre wacrenier
//

#include <string>

#include <X11/Xlib.h>

namespace ZX
{
  class Display
  {
  private:
    static Display *	_instance;
    ::Display *		_dpy;
    std::string		_name;

    Display(void);
    Display(const std::string & name);
    Display(const Display &);				// not implemented

    Display&		operator=(const Display &);	// not implemented

    virtual ~Display();

    static void		destroyInstance(void);

  public:
    static Display &	getInstance(void);
    static Display &	getInstance(const std::string & name);
    bool		isOpen(void) const;
    ::Display *		getDisplay(void) const;
    std::string		getName(void) const;
  };
}
