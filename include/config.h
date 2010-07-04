#ifndef		CONFIG_H_
# define	CONFIG_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define ModKey Mod4Mask

Layout		layouts[] =
  {
    {"[]=",	layout_tile	},
    {"[O]",	layout_monocle	},
    {"TT",	layout_htile	},
    {"=[]=",	layout_mirror	},
  };

#define	FOCUS_FOLLOWS_MOUSE	false
#define	MASTER_WIDTH		0.7
#define	MASTER_SIZE		1
#define	FOCUS_COLOR		"#990000"
#define	UNFOCUS_COLOR		"#838383"
#define BAR_HEIGHT		0

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
    SET_WORKSPACE("0"),
  };

/*
** Set on which workspaces a class is affected in, starting by 0
*/

Application	rules[] =
  {
    {"Firefox",		2},
    {"Gvim",		1}
  };

/*
** Must be NULL-terminated
*/

const char *xtermcmd[] = {"xterm", NULL};
const char *dmenucmd[] =
  {"dmenu_run", "-nb", "#252525", "-nf", "#e3e3e3", "-sb", "#1e5e8a", NULL};

#define	WORKSPACE_KEY(KEY, WRKSP)					\
  {ModKey,		(KEY),		change_workspace,	{.val = WRKSP}	}, \
  {ModKey|ShiftMask,	(KEY),		move_to_workspace,	{.val = WRKSP}	},

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
  {ModKey,		XK_n,		move_window,	{.val = +1}		},
  {ModKey,		XK_p,		move_window,	{.val = -1}		},
  WORKSPACE_KEY(	XK_1,				0			)
  WORKSPACE_KEY(	XK_2,				1			)
  WORKSPACE_KEY(	XK_3,				2			)
  WORKSPACE_KEY(	XK_4,				3			)
  WORKSPACE_KEY(	XK_5,				4			)
  WORKSPACE_KEY(	XK_6,				5			)
  WORKSPACE_KEY(	XK_7,				6			)
  WORKSPACE_KEY(	XK_8,				7			)
  WORKSPACE_KEY(	XK_9,				8			)
  WORKSPACE_KEY(	XK_0,				9			)
};

#endif		/* !CONFIG_H_ */
