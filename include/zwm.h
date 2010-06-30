#ifndef		ZWM_H_
# define	ZWM_H_

#include <X11/Xlib.h>
#include <X11/keysym.h>

#define	TABLELENGTH(X) (sizeof((X)) / sizeof(*(X)))

typedef struct _Client
{
  t_elem	self;
  Window	win;
}		Client;

typedef struct	_Workspace
{
  t_list	windows;
  Client	*focus;
  char		*repr;
}		Workspace;

typedef struct	_Conf
{
  double	master_width;
  char		*border_focus;
  char		*border_unfocus;
}		Conf;

typedef struct	_Wm
{
  unsigned int	cur_workspace;
  Workspace	*workspaces;
  Conf		*conf;
  Display	*dpy;
  int		screen;
  Window	root;
}		Wm;

typedef union	_Arg
{
  int		val;
  char		*args;
}		Arg;

typedef struct	_Key
{
  unsigned int	mod;
  KeySym	key;
  void		(*func)(const Arg *arg);
  Arg		arg;
}		Key;

#endif		/* !ZWM_H_ */
