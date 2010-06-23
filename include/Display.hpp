#include <string>

#include <X11/Xlib.h>

namespace ZX
{
  class Display
  {
  private:
    static Display *	_instance;
    ::Display *		_dpy;
    int			_screen;
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
    int			getScreen(void) const;
  };
}
