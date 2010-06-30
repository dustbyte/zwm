/*
** list_search.c for src in /afs/epitech.net/users/epitech_2013/appere_n/cu/projets/zappy/server/libs/lists/src
**
** Made by pierre wacrenier
** Login   <wacren_p@epitech.net>
**
** Started on  Sat Jun 12 17:08:25 2010 pierre wacrenier
** Last update Tue Jun 15 18:05:06 2010 nathan appere
*/

#include <stdlib.h>

#include "lists.h"

t_elem		*list_find_elem(t_list *list, void *data)
{
  t_elem	*elem;

  list_foreach(list->head, elem)
    if (elem->data == data)
      return (elem);
  return (NULL);
}

t_elem		*list_get_elem(t_list *list, size_t iter)
{
  t_elem	*elem;

  list_foreach(list->head, elem)
    if (--iter == 0)
      return (elem);
  return (NULL);
}
