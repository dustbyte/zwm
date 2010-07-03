TYPE		=	$(shell uname -s)
TYPE		!=	uname -s

NAME		=	zwm

CC		=	gcc
CD		=	cd
MAKE		=	make
CP		=	cp -r
RM		=	rm -rf
FIND		=	find

LOG		=	liblog.a
LOGDIR		=	$(LIBDIR)/log

LISTS		=	liblists.a
LISTSDIR	=	$(LIBDIR)/lists

LIBDIR		=	libs

CFLAGS		+=	-O2 -Werror -DNDEBUG
CFLAGS		=	-g3
CFLAGS		+=	-W -Wall -pedantic -std=c99
CFLAGS		+=	-D${TYPE} -D_REENTRANT -D__EXTENSIONS__
CFLAGS		+=	-D_POSIX_PTHREAD_SEMANTICS -D_BSD_SOURCE -D_GNU_SOURCE

CFLAGS		+=	-I$(HDRDIR) -I/usr/X11R6/include -I$(LOGDIR)/include -I$(LISTSDIR)/include

LDFLAGS		=	-L/usr/X11R6/lib -lX11 -L$(LIBDIR) -llog -llists			\
			-Wl,--start-group $(LIBDIR)/$(LOG) $(LIBDIR)/$(LISTS) --end-group

SRCDIR		=	src
HDRDIR		=	include

SRCS		=	$(SRCDIR)/commands/change_desktop.c	\
			$(SRCDIR)/commands/kill_client.c	\
			$(SRCDIR)/commands/master_size.c	\
			$(SRCDIR)/commands/move_focus.c		\
			$(SRCDIR)/commands/move_window.c	\
			$(SRCDIR)/commands/quit.c		\
			$(SRCDIR)/commands/resize.c		\
			$(SRCDIR)/commands/spawn.c		\
			$(SRCDIR)/commands/switch_layout.c	\
			$(SRCDIR)/commands/zoom.c		\
			$(SRCDIR)/layouts/htile.c		\
			$(SRCDIR)/layouts/mirror.c		\
			$(SRCDIR)/layouts/monocle.c		\
			$(SRCDIR)/layouts/tile.c		\
			$(SRCDIR)/tools.c			\
			$(SRCDIR)/windows.c			\
			$(SRCDIR)/zwm.c

OBJS		=	$(SRCS:.c=.o)

HDRS		=

$(NAME):		lib_log lib_lists $(SRCS) $(OBJS) $(HDRS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)


# Dependencies -----------------------------------------------------------------

lib_log:
			$(CD) $(LOGDIR); $(MAKE) "CFLAGS=$(CFLAGS)" all
			$(CP) $(LOGDIR)/$(LOG) $(LIBDIR)

clean_lib_log:
			$(CD) $(LOGDIR); $(MAKE) fclean

lib_lists:
			$(CD) $(LISTSDIR); $(MAKE) "CFLAGS=$(CFLAGS)" all
			$(CP) $(LISTSDIR)/$(LISTS) $(LIBDIR)

clean_lib_lists:
			$(CD) $(LISTSDIR); $(MAKE) fclean

# Common ----------------------------------------------------------------------

all:			$(NAME)

clean:
			$(RM) $(OBJS)
			$(RM) $(LIBDIR)/*.a
			$(FIND) . -name "*~" -print -exec rm -f {} \;
			$(FIND) . -name "*\#*" -print -exec rm -f {} \;
			$(RM) $(NAME).core
			$(RM) vgcore*

fclean:			clean clean_lib_log clean_lib_lists
			$(RM) $(NAME)
			$(RM) TAGS

mrproper:		$(NAME) clean

re:			fclean $(NAME)

.c.o:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY:			clean all fclean mrproper re
