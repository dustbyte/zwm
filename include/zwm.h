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
  unsigned int		x;
  unsigned int		y;
  unsigned int		width;
  unsigned int		height;
  unsigned int		border_width;
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
  t_list		exec_list;
  Display		*dpy;
  int			screen;
  Window		parent;
  Window		win;
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

void		configure(Wm *wm, Client *c);
void		draw(Wm *wm);
void		undraw(Wm *wm);
void		redraw(Wm *wm);
void		sigchld(int unused);
void		update_wm_hints(Wm *wm, Client *client);

/*
** Handlers
*/

void		key_press(Wm *wm, XEvent *event);
void		map_request(Wm *wm, XEvent *event);
void		button_press(Wm *wm, XEvent *event);
void		enter_notify(Wm *wm, XEvent *event);
void		motion_notify(Wm *wm, XEvent *event);
void		destroy_notify(Wm *wm, XEvent *event);
void		configure_request(Wm *wm, XEvent *event);
void		configure_notify(Wm *wm, XEvent *event);
void		property_notify(Wm *wm, XEvent *event);
void		unmap_notitfy(Wm *wm, XEvent *event);

/*
** Windows
*/

Client		*add_window(Wm *wm, Window window);
void		remove_window(Wm *wm, Client *win);
Client		*get_window(Wm *wm, Window window);
void		set_win_attributes(Client *client,
				   unsigned int x, unsigned int y,
				   unsigned int width, unsigned int height,
				   unsigned int border_width);
void		move_resize_window(Wm *wm, Client *client,
				   unsigned int x, unsigned int y,
				   unsigned int width, unsigned int height);
void		base_move_resize_window(Wm *wm, Client *client);
void		border_width_window(Wm *wm, Client *client, unsigned int width);
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
void		zmenu_run(const Arg *arg);

/*
** Layouts
*/

void		layout_tile(Wm *wm);
void		layout_htile(Wm *wm);
void		layout_monocle(Wm *wm);
void		layout_mirror(Wm *wm);

/*
** Zmenu
*/

int		zmenu(Wm *wm);

#endif		/* !ZWM_H_ */
