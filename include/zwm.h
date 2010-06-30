#ifndef		ZWM_H_
# define	ZWM_H_

#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "lists.h"

#define	TABLELENGTH(X) (sizeof((X)) / sizeof(*(X)))

typedef struct _Client
{
  t_elem	self;
  Window	win;
}		Client;

typedef struct	_Workspace
{
  t_list	windows;
  int		master_size;
  Bool		stacked;
  Client	*focus;
  char		*repr;
}		Workspace;

typedef struct	_ZWindow
{
  t_elem	self;
  Window	win;
}		ZWindow;

typedef struct	_Conf
{
  double	master_width;
  char		*border_focus;
  char		*border_unfocus;
}		Conf;

typedef struct	_Wm
{
  Workspace	*cur_workspace;
  Workspace	*workspaces;
  Conf		*conf;
  Display	*dpy;
  int		screen;
  Window	root;
  Bool		is_running;

}		Wm;

typedef union	_Arg
{
  int		val;
  const void	*args;
}		Arg;

typedef struct	_Key
{
  unsigned int	mod;
  KeySym	keysym;
  void		(*func)(const Arg *arg);
  Arg		arg;
}		Key;

/*
** Handlers
*/

void		key_press(Wm *wm, XEvent *event);
void		map_request(Wm *wm, XEvent *event);
void		destroy_notify(Wm *wm, XEvent *event);

/*
** Windows
*/

void		add_window(Wm *wm, Window window);
void		remove_window(Wm *wm, Window window);

/*
** Commands
*/

void		spawn(const Arg *arg);

#endif		/* !ZWM_H_ */
