/*
** lists.c for src in /usr/home/me/projets/zappy/server/libs/lists/src
**
** Made by pierre wacrenier
** Login   <wacren_p@epitech.net>
**
** Started on  Wed Jun  9 13:20:39 2010 pierre wacrenier
** Last update Fri Jun 25 13:41:28 2010 nathan appere
*/

#include <stdlib.h>
#include <stdio.h>

#include "lists.h"

void		list_init(t_list *list)
{
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
}

void		list_show(t_list *list, void (*show_func)(void *data))
{
  t_elem	*tmp;
#if !defined(NDEBUG)
  printf(">>>List size: %u<<<\n", (unsigned int)list->size);
  list_foreach(list->head, tmp)
    show_func(tmp->data);
#else
  (void)tmp;
  (void)list;
  (void)show_func;
#endif

}
