TYPE		=	$(shell uname -s)
TYPE		!=	uname -s

NAME		=	zmenu
NAME_PATH	=	$(NAME)_path
NAME_RUN	=	$(NAME)_run

CC		=	gcc
CD		=	cd
MAKE		=	make
CP		=	cp -r
RM		=	rm -rf
FIND		=	find

LISTS		=	liblists.a
LISTSDIR	=	$(LIBDIR)/lists

LIBDIR		=	../libs

INSTALLDIR	=	$(HOME)/bin

CFLAGS		+=	-O2 -Werror -DNDEBUG
CFLAGS		=	-g3
CFLAGS		+=	-W -Wall -pedantic -std=c99
CFLAGS		+=	-D${TYPE} -D_REENTRANT -D__EXTENSIONS__
CFLAGS		+=	-D_POSIX_PTHREAD_SEMANTICS -D_BSD_SOURCE -D_GNU_SOURCE

CFLAGS		+=	-I$(HDRDIR) -I/usr/X11R6/include -I$(LISTSDIR)/include

LDFLAGS		=	-L/usr/X11R6/lib -lX11 -L$(LIBDIR) -llists

SRCDIR		=	src
HDRDIR		=	include

SRCS		=	$(SRCDIR)/zmenu.c

OBJS		=	$(SRCS:.c=.o)

HDRS		=

$(NAME):		lib_lists $(SRCS) $(OBJS) $(HDRS)
			$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)


# Dependencies -----------------------------------------------------------------

lib_lists:
			$(CD) $(LISTSDIR); $(MAKE) "CFLAGS=$(CFLAGS)" all
			$(CP) $(LISTSDIR)/$(LISTS) $(LIBDIR)

clean_lib_lists:
			$(CD) $(LISTSDIR); $(MAKE) fclean

# Common ----------------------------------------------------------------------

all:			$(NAME)

install:		all
			$(CP) $(NAME) $(INSTALLDIR)/$(NAME)
			$(CP) $(NAME_PATH) $(INSTALLDIR)/$(NAME_PATH)
			$(CP) $(NAME_RUN) $(INSTALLDIR)/$(NAME_RUN)

deinstall:
			$(RM) $(INSTALLDIR)/$(NAME)
			$(RM) $(INSTALLDIR)/$(NAME_PATH)
			$(RM) $(INSTALLDIR)/$(NAME_RUN)

clean:
			$(RM) $(OBJS)
			$(RM) $(LIBDIR)/*.a
			$(FIND) . -name "*~" -print -exec rm -f {} \;
			$(FIND) . -name "*\#*" -print -exec rm -f {} \;
			$(RM) $(NAME).core
			$(RM) vgcore*

fclean:			clean clean_lib_lists
			$(RM) $(NAME)
			$(RM) TAGS

mrproper:		$(NAME) clean

re:			fclean $(NAME)

.c.o:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY:			clean all fclean mrproper re
