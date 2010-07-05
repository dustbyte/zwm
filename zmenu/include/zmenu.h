#ifndef		ZMENU_H_
# define	ZMENU_H_

#define		PROGNAME	"zmenu"
#define		VERSION		"0.1"

#define		BUFSIZE		4096

typedef int	(*cmpfunc)(const char *s1, const char *s2, size_t len);

typedef struct	_Conf
{
  Bool		top;
  cmpfunc	cmp;
  char		*font;
  char		*n_bgcolor;
  char		*n_fgcolor;
  char		*s_bgcolor;
  char		*s_fgcolor;
  unsigned int	x;
  unsigned int	y;
  unsigned int	height;
  unsigned int	width;
  unsigned int	space;
}		Conf;

typedef struct _DrawConf
{
  XFontStruct	*font_info;
  GC		normal;
  GC		selected;
}		DrawConf;

typedef struct	_Item
{
  t_elem	self;
  char		*name;
}		Item;

typedef struct	_ZMenu
{
  Display	*dpy;
  Window	root;
  int		screen;
  Window	win;
  Conf		*conf;
  DrawConf	dconf;
  Bool		is_running;
  t_list	items;
  unsigned int	max;
}		ZMenu;

GC		create_gc(ZMenu *zm, unsigned int bg, unsigned int fg);
void		create_widow(ZMenu *zm);
void		die(const char *fmt, ...);
unsigned long	get_color(ZMenu *zm, const char *color);
int		item_cmp(void *item1, void *item2);
void		read_stdin(ZMenu *zm);
void		setup(ZMenu *zm, Conf *conf);
void		setup_conf(int ac, char **av, Conf *conf);
void		usage(void);

#endif		/* !ZMENU_H_ */
