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
