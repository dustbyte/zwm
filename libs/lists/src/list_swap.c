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
