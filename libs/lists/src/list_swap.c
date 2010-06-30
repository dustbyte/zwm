/*
** zp_list_swap.c for src in /home/mota/projets/tek2/zappy/server/libs/lists/src
**
** Made by pierre wacrenier
** Login   <wacren_p@epitech.net>
**
** Started on  Wed Jun  9 14:27:04 2010 pierre wacrenier
** Last update Mon Jun 14 14:18:30 2010 Pierre Wacrenier
*/

#include <stdlib.h>

#include "lists.h"

int		elem_swap_next(t_elem *elem)
{
  void		*tmp;

  if (elem->next == NULL)
    return (-1);
  tmp = elem->next->data;
  elem->next->data = elem->data;
  elem->data = tmp;
  return (0);
}

int		elem_swap_prev(t_elem *elem)
{
  void		*tmp;

  if (elem->prev == NULL)
    return (-1);
  tmp = elem->prev->data;
  elem->prev->data = elem->data;
  elem->data = tmp;
  return (0);
}
