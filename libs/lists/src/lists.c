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
