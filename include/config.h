#ifndef		CONFIG_H_
# define	CONFIG_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define ModKey Mod4Mask

#define	SET_WORKSPACE(X) {{0, NULL, NULL}, 1, false, NULL, (X)}

Workspace	workspaces[] =
  {
    SET_WORKSPACE("0"),
    SET_WORKSPACE("1"),
    SET_WORKSPACE("2"),
    SET_WORKSPACE("3"),
    SET_WORKSPACE("4"),
    SET_WORKSPACE("5"),
    SET_WORKSPACE("6"),
    SET_WORKSPACE("7"),
    SET_WORKSPACE("8"),
    SET_WORKSPACE("9")
  };

Conf		conf =
  {
    0.7,
    "#ffffff",
    "#838383"
  };

const char *xtermcmd[] = {"xterm", NULL};

const Key keys[] =
{
  {ModKey,		XK_Return,	NULL,	{.args = xtermcmd}	},
  {ModKey,		XK_h,		NULL,	{.val = -1}		}
};

#endif		/* !CONFIG_H_ */
