##
## Makefile for lists in /afs/epitech.net/users/epitech_2013/appere_n/cu/projets/zappy/server/libs/lists
##
## Made by pierre wacrenier
## Login   <wacren_p@epitech.net>
##
## Started on  Mon Jun  7 16:13:16 2010 pierre wacrenier
## Last update Tue Jun 15 23:56:28 2010 pierre wacrenier
##

TYPE		=	$(shell uname -s)
TYPE		!=	uname -s

NAME		=	liblists.a

CC		=	gcc
CD		=	cd
AR		=	ar rcs
RANLIB		=	ranlib

RM		=	rm -rf
FIND		=	find

ZP_LOGDIR	=	../log
ZP_LOG		=	liblog.a

LIBDIR		=	..

CFLAGS		+=	-O2 -Werror
CFLAGS		=	-g3
CFLAGS		+=	-W -Wall -ansi -pedantic
CFLAGS		+=	-D${TYPE} -D_REENTRANT -D__EXTENSIONS__
CFLAGS		+=	-D_POSIX_PTHREAD_SEMANTICS -D_BSD_SOURCE -D_GNU_SOURCE

CFLAGS		+=	-I$(HDRDIR) -I../log/include

LDFLAGS		=

SRCDIR		=	src
HDRDIR		=	include

SRCS		=	$(SRCDIR)/list_elem.c		\
			$(SRCDIR)/list_insertion.c	\
			$(SRCDIR)/list_move.c		\
			$(SRCDIR)/list_search.c		\
			$(SRCDIR)/list_swap.c		\
			$(SRCDIR)/lists.c		\
			$(SRCDIR)/list_deletion.c	\
			$(SRCDIR)/list_free.c

OBJS		=	$(SRCS:.c=.o)

HDRS		=

$(NAME):		lib_log $(SRCS) $(OBJS) $(HDRS)
			$(AR) $(NAME) $(OBJS)

# Dependencies -----------------------------------------------------------------

lib_log:
			$(CD) $(ZP_LOGDIR); $(MAKE) all

clean_lib_log:
			$(CD) $(ZP_LOGDIR); $(MAKE) fclean


# Common ----------------------------------------------------------------------

all:			$(NAME)

clean:
			$(RM) $(OBJS)
			$(FIND) . -name "*~" -print -exec rm -f {} \;
			$(FIND) . -name "*\#*" -print -exec rm -f {} \;
			$(RM) $(NAME).core

fclean:			clean
			$(RM) $(NAME)
			$(RM) TAGS

mrproper:		$(NAME) clean

armageddon:		$(RM) $(SRCDIR) $(HDRDIR)

re:			fclean $(NAME)

tags:
			etags `find . -name "*.[ch]"`

.c.o:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY:			clean all fclean mrproper re
