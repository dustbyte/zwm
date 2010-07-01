#ifndef		CONFIG_H_
# define	CONFIG_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define ModKey Mod4Mask

Layout		layouts[] =
  {
    {"[]=",	layout_tile	},
    {"[O]",	layout_monocle	},
    /* {"[]~",	NULL		} */
  };

#define	MASTER_WIDTH	0.7
#define	MASTER_SIZE	1

#define	SET_WORKSPACE(X) {{0, NULL, NULL}, MASTER_SIZE, MASTER_WIDTH, NULL, (X), 0}

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
    "#990000",
    "#838383"
  };

const char *xtermcmd[] = {"rxvt", NULL};
const char *dmenucmd[] = {"dmenu_run", NULL};

const Key keys[] =
{
  {ModKey,		XK_Return,	spawn,		{.args = xtermcmd}	},
  {ModKey,		XK_a,		spawn,		{.args = dmenucmd}	},
  {ModKey|ShiftMask,	XK_e,		quit,		{0}			},
  {ModKey,		XK_k,		move_focus,	{.val = -1}		},
  {ModKey,		XK_j,		move_focus,	{.val = +1}		},
  {ModKey,		XK_Right,	switch_layout,	{.val = +1}		},
  {ModKey,		XK_Left,	switch_layout,	{.val = -1}		},
  {ModKey|ShiftMask,	XK_k,		master_size,	{.val = +1}		},
  {ModKey|ShiftMask,	XK_j,		master_size,	{.val = -1}		},
  {ModKey,		XK_h,		resize,		{.dval = -0.05}		},
  {ModKey,		XK_l,		resize,		{.dval = +0.05}		},
  {ModKey,		XK_space,	zoom,		{0}			},
};

#endif		/* !CONFIG_H_ */
