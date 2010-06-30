##
## Makefile for zappy in /home/mota/projets/tek2/zappy/server/log
##
## Made by pierre wacrenier
## Login   <wacren_p@epitech.net>
##
## Started on  Mon Jun  7 16:13:16 2010 pierre wacrenier
## Last update Mon Jun 14 18:14:37 2010 pierre wacrenier
##

TYPE		=	$(shell uname -s)
TYPE		!=	uname -s

NAME		=	liblog.a

CC		=	gcc
AR		=	ar rcs
RANLIB		=	ranlib

RM		=	rm -rf
FIND		=	find

CFLAGS		+=	-O2 -Werror
CFLAGS		=	-g3
CFLAGS		+=	-W -Wall -ansi -pedantic
CFLAGS		+=	-D${TYPE} -D_REENTRANT -D__EXTENSIONS__
CFLAGS		+=	-D_POSIX_PTHREAD_SEMANTICS -D_BSD_SOURCE -D_GNU_SOURCE

CFLAGS		+=	-I$(HDRDIR)

LDFLAGS		=

SRCDIR		=	src
HDRDIR		=	include

SRCS		=	$(SRCDIR)/log.c

OBJS		=	$(SRCS:.c=.o)

HDRS		=

$(NAME):		$(SRCS) $(OBJS) $(HDRS)
			$(AR) $(NAME) $(OBJS)

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
