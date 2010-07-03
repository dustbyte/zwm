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

typedef struct		_Colors
{
  unsigned int		focus;
  unsigned int		unfocus;
}			Colors;

typedef struct		_Zmenu
{
  enum {
    ZMENU_NORMAL = 0,
    ZMENU_CALL,
    ZMENU_RUN
  }			status;
  char			buf[4096];
  char			**exec_list;
  /* Ajouter conf */
}			Zmenu;

typedef struct		_Wm
{
  unsigned int		cwrksp;
  Workspace		*workspaces;
  Colors		colors;
  Display		*dpy;
  int			screen;
  Window		root;
  int			scr_width;
  int			scr_height;
  Bool			is_running;
  unsigned int		layouts_number;
  unsigned int		bar_height;
  struct _Layout	*layouts;
  struct _Zmenu		zmenu;
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
void		undraw(Wm *wm);
void		redraw(Wm *wm);
/*
** Handlers
*/

void		key_press(Wm *wm, XEvent *event);
void		map_request(Wm *wm, XEvent *event);
void		enter_notify(Wm *wm, XEvent *event);
void		destroy_notify(Wm *wm, XEvent *event);
void		configure_request(Wm *wm, XEvent *event);
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
void		kill_client(const Arg *arg);
void		change_desktop(const Arg *arg);
void		move_window(const Arg *arg);

/*
** Layouts
*/

void		layout_tile(Wm *wm);
void		layout_htile(Wm *wm);
void		layout_monocle(Wm *wm);
void		layout_mirror(Wm *wm);

#endif		/* !ZWM_H_ */
