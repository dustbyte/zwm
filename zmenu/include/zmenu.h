#ifndef		ZMENU_H_
# define	ZMENU_H_

#define		PROGNAME	"zmenu"
#define		VERSION		"0.1"

#define		BUFSIZE		4096
#define		DFL_HEIGHT	17

typedef int	(*cmpfunc)(const char *s1, const char *s2, size_t len);

typedef struct	_Color
{
  unsigned int	bg;
  unsigned int	fg;
}		Color;

typedef struct	_Conf
{
  Bool		top;
  Bool		icase;
  char		*font;
  char		*n_bgcolor;
  char		*n_fgcolor;
  char		*s_bgcolor;
  char		*s_fgcolor;
  unsigned int	x;
  unsigned int	height;
  unsigned int	width;
  unsigned int	space;
}		Conf;

typedef struct	_Dims
{
  unsigned int	x;
  unsigned int	y;
  unsigned int	width;
  unsigned int	height;
}		Dims;

typedef struct _DrawConf
{
  XFontStruct	*font_info;
  GC		gc;
  Color		n;
  Color		s;
}		DrawConf;

typedef struct	_Item
{
  t_elem	self;
  t_elem	match;
  char		*name;
}		Item;

typedef struct	_ZMenu
{
  Display	*dpy;
  Window	root;
  int		screen;
  Window	win;
  unsigned int	scr_width;
  unsigned int	scr_height;
  Conf		*conf;
  cmpfunc	cmp;
  DrawConf	dconf;
  Bool		is_running;
  t_list	items;
  t_list	match;
  Item		*selected;
  Drawable	dw;
  unsigned int	max;
  char		buf[BUFSIZE];
}		ZMenu;

GC		create_gc(ZMenu *zm, unsigned int bg, unsigned int fg);
void		create_widow(ZMenu *zm);
void		die(const char *fmt, ...);
void		draw_menu(ZMenu *zm);
int		draw_text(ZMenu *zm, Color *color, Dims *dims, char *str);
void		finish(ZMenu *zm);
unsigned long	get_color(ZMenu *zm, const char *color);
void		grab_keyboard(ZMenu *zm);
int		item_cmp(void *item1, void *item2);
void		item_free(void *it);
void		item_shot(void *it);
void		read_stdin(ZMenu *zm);
void		run(ZMenu *zm);
void		setup(ZMenu *zm, Conf *conf);
void		setup_conf(int ac, char **av, Conf *conf);
int		text_width(ZMenu *zm, char *str);
void		usage(void);

#endif		/* !ZMENU_H_ */
