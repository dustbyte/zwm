#include <stdlib.h>

#include "lists.h"

t_elem		*list_remove(t_list *list, t_elem *elem)
{
  if (elem->prev != NULL)
    elem->prev->next = elem->next;
  else
    list->head = elem->next;
  if (elem->next != NULL)
    elem->next->prev = elem->prev;
  else
    list->tail = elem->prev;
  elem->prev = elem->next = NULL;
  --list->size;
  return (elem);
}

int		list_delete(t_list *list, t_elem *self,
			    void (*free_func)(void *data))
{
  list_remove(list, self);
  free_func(self->data);
  if (list->head == NULL)
    return (1);
  return (0);
}

void		list_empty(t_list *list, void (*free_func)(void *data))
{
  t_elem	*tmp;
  t_elem	*next;

  for (tmp = list->head; tmp != NULL; tmp = next)
    {
      next = tmp->next;
      free_func(tmp->data);
    }
  list->head = list->tail = NULL;
  list->size = 0;
}
