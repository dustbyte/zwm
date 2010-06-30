#include <stdlib.h>
#include <stdio.h>

#include "lists.h"

void		elem_push_back(t_list *list, t_elem *self,
			       t_elem *prev, void *data)
{
  if (list->head == NULL)
    list_add_tail(list, self, data);
  else
    {
      self->data = data;
      self->prev = prev;
      self->next = NULL;
      if (prev != NULL)
	{
	  self->next = prev->next;
	  prev->next = self;
	}
      if (self->next != NULL)
	self->next->prev = self;
      if (list->tail == prev)
	list->tail = self;
      ++list->size;
    }
}

void		elem_push_front(t_list *list, t_elem *self,
				t_elem *next, void *data)
{
  if (list->head == NULL)
    list_add_tail(list, self, data);
  else
    {
      self->data = data;
      self->prev = NULL;
      self->next = next;
      if (next != NULL)
	{
	  self->prev = next->prev;
	  next->prev = self;
	}
      if (self->prev != NULL)
	self->prev->next = self;
      if (list->head == next)
	list->head = self;
      ++list->size;
    }
}
