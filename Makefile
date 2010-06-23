##
## Makefile for zwm in /home/mota/projets/tek2/zwm
##
## Made by pierre wacrenier
## Login   <wacren_p@epitech.net>
##
## Started on  Mon May  3 16:39:13 2010 pierre wacrenier
## Last update Wed Jun 23 17:14:47 2010 pierre wacrenier
##

TYPE		=	$(shell uname -s)
TYPE		!=	uname -s

NAME		=	zwm

CXX		=	g++

RM		=	rm -rf
FIND		=	find

CXXFLAGS	=	-W -Wall -Werror -pedantic -Wmissing-braces
#CXXFLAGS	+=	-pipe -O2
CXXFLAGS	+=	-g3
CXXFLAGS	+=	-D${TYPE} -D_REENTRANT -D__EXTENSIONS__
CXXFLAGS	+=	-D_POSIX_PTHREAD_SEMANTICS -D_BSD_SOURCE -D_GNU_SOURCE

CXXFLAGS	+=	-I$(HDRDIR) -I/usr/X11R6/include

LDFLAGS		=	-L/usr/X11R6/lib -lX11

SRCDIR		=	src
HDRDIR		=	include

SRCS		=	$(SRCDIR)/ZXlib/ZDisplay.cpp	\
			$(SRCDIR)/main.cpp

OBJS		=	$(SRCS:.cpp=.o)

HDRS		=

$(NAME):		$(SRCS) $(OBJS) $(HDRS)
			$(CXX) $(OBJS) -o $(NAME) $(LDFLAGS)

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

re:			fclean $(NAME)

tags:
			ctags `find . -name "*.[ch]"`

.cpp.o:
			$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

.PHONY:			clean all fclean mrproper re
