#ifndef		ZWM_H_
# define	ZWM_H_

#include <stdbool.h>

#include <X11/Xlib.h>
#include <X11/keysym.h>

#include "lists.h"

#define	TABLELENGTH(X) (sizeof((X)) / sizeof(*(X)))

typedef struct		_Client
{
  t_elem		self;
  Window		win;
}			Client;

typedef struct		_Workspace
{
  t_list		windows;
  unsigned int		master_size;
  double		master_width;
  Client		*focus;
  char			*repr;
  unsigned int		layout;
}			Workspace;

typedef struct		_Conf
{
  char			*border_focus;
  char			*border_unfocus;
}			Conf;

typedef struct		_Colors
{
  unsigned int		focus;
  unsigned int		unfocus;
}			Colors;

typedef struct		_Wm
{
  unsigned int		cwrksp;
  Workspace		*workspaces;
  Conf			*conf;
  Colors		colors;
  Display		*dpy;
  int			screen;
  Window		root;
  int			scr_width;
  int			scr_height;
  Bool			is_running;
  unsigned int		layouts_number;
}			Wm;

typedef struct		_Layout
{
  char			*name;
  void			(*func)(Wm *wm);
}			Layout;

typedef union		_Arg
{
  int			val;
  double		dval;
  const void		*args;
}			Arg;

typedef struct		_Key
{
  unsigned int		mod;
  KeySym		keysym;
  void			(*func)(const Arg *arg);
  Arg			arg;
}			Key;

/*
** General
*/

void		draw(Wm *wm);

/*
** Handlers
*/

void		key_press(Wm *wm, XEvent *event);
void		map_request(Wm *wm, XEvent *event);
void		destroy_notify(Wm *wm, XEvent *event);
void		configure_notify(Wm *wm, XEvent *event);

/*
** Windows
*/

void		add_window(Wm *wm, Window window);
void		remove_window(Wm *wm, Client *win);
Client		*get_window(Wm *wm, Window window);

/*
** Commands
*/

void		resize(const Arg *arg);
void		spawn(const Arg *arg);
void		quit(const Arg *arg);
void		move_focus(const Arg *arg);
void		switch_layout(const Arg *arg);
void		zoom(const Arg *arg);
void		master_size(const Arg *arg);
/*
** Layouts
*/

void		draw(Wm *wm);
void		layout_tile(Wm *wm);
void		layout_monocle(Wm *wm);

#endif		/* !ZWM_H_ */
