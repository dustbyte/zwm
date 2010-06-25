#ifndef DISPLAY_HPP_
#define DISPLAY_HPP_

#include <string>

#include <X11/Xlib.h>

namespace ZX
{
  class Display
  {
  private:
    static Display *	mInstance;
    ::Display *		mDpy;
    int			mScreen;
    std::string		mName;

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
    int			getScreen(void) const;
  };
}

#endif		// DISPLAY_HPP_
