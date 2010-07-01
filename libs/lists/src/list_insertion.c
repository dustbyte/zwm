#include <stdlib.h>
#include <stdio.h>

#include "lists.h"

void		list_add_tail(t_list *list, t_elem *self, void *data)
{
  self->data = data;
  self->prev = list->tail;
  self->next = NULL;
  if (list->tail != NULL)
    list->tail->next = self;
  else
    list->head = self;
  list->tail = self;
  ++list->size;
}

void		list_add_head(t_list *list, t_elem *self, void *data)
{
  self->data = data;
  self->prev = NULL;
  self->next = list->head;
  if (list->head != NULL)
    list->head->prev = self;
  else
    list->tail = self;
  list->head = self;
  ++list->size;
}

void		list_insert(t_list *list,
			    t_elem *self,
			    void *data,
			    int (*cmp_func)(void *data1, void *data2))
{
  t_elem	*tmp;
  int		cmp_res;

  list_foreach(list->head, tmp)
    {
      if ((cmp_res = cmp_func(data, tmp->data)) > 0)
	{
	  elem_push_front(list, self, tmp, data);
	  return ;
	}
      else if (cmp_res == 0)
	{
	  elem_push_back(list, self, tmp, data);
	  return ;
	}
    }
  list_add_tail(list, self, data);
}
