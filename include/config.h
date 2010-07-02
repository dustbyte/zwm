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
#define	FOCUS_COLOR	"#990000"
#define	UNFOCUS_COLOR	"#838383"
#define BAR_HEIGHT	0

#define	SET_WORKSPACE(X) {{0, NULL, NULL}, MASTER_SIZE, MASTER_WIDTH, NULL, (X), 0}

Workspace	workspaces[] =
  {
    SET_WORKSPACE("1"),
    SET_WORKSPACE("2"),
    SET_WORKSPACE("3"),
    SET_WORKSPACE("4"),
    SET_WORKSPACE("5"),
    SET_WORKSPACE("6"),
    SET_WORKSPACE("7"),
    SET_WORKSPACE("8"),
    SET_WORKSPACE("9"),
    SET_WORKSPACE("0")
  };

const char *xtermcmd[] = {"rxvt", NULL};
const char *dmenucmd[] =
  {"dmenu_run", "-nb", "#252525", "-nf", "#e3e3e3", "-sb", "#1e5e8a"};

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
  {ModKey|ShiftMask,	XK_q,		kill_client,	{0}			},
  {ModKey,		XK_1,		change_desktop,	{.val = 0}		},
  {ModKey,		XK_2,		change_desktop,	{.val = 1}		},
  {ModKey,		XK_3,		change_desktop,	{.val = 2}		},
  {ModKey,		XK_4,		change_desktop,	{.val = 3}		},
  {ModKey,		XK_5,		change_desktop,	{.val = 4}		},
  {ModKey,		XK_6,		change_desktop,	{.val = 5}		},
  {ModKey,		XK_7,		change_desktop,	{.val = 6}		},
  {ModKey,		XK_8,		change_desktop,	{.val = 7}		},
  {ModKey,		XK_9,		change_desktop,	{.val = 8}		},
  {ModKey,		XK_0,		change_desktop,	{.val = 9}		},
};

#endif		/* !CONFIG_H_ */
