/*
** list_elem.c for src in /home/mota/projets/tek2/zappy/server/libs/lists/src
**
** Made by pierre wacrenier
** Login   <wacren_p@epitech.net>
**
** Started on  Sat Jun 12 15:49:04 2010 pierre wacrenier
** Last update Fri Jun 18 17:35:27 2010 pierre wacrenier
*/

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
