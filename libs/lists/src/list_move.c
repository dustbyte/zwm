/*
** list_move.c for src in /usr/home/me/projets/zappy/server/libs/lists/src
**
** Made by pierre wacrenier
** Login   <wacren_p@epitech.net>
**
** Started on  Thu Jun 17 02:09:13 2010 pierre wacrenier
** Last update Fri Jun 25 14:31:23 2010 nathan appere
*/

#include <assert.h>
#include <stdlib.h>

#include "lists.h"

void		list_move_head_to_head_all(t_list *src,
					   t_list *dest)
{
  if (src->head == NULL)
    return ;
  assert(src->tail != NULL && src->head != NULL);
  src->tail->next = dest->head;
  if (dest->head != NULL)
    dest->head->prev = src->tail;
  else
    dest->tail = src->tail;
  dest->head = src->head;
  dest->size += src->size;
  src->head = src->tail = NULL;
  src->size = 0;
}

void		list_move_head_to_head(t_list *src,
				       t_list *dest,
				       unsigned int n)
{
  t_elem	*first;
  t_elem	*last;

  assert(src->size >= n);
  first = src->head;
  last = list_get_elem(src, n);
  assert(last != NULL);
  if (last->next != NULL)
    last->next->prev = NULL;
  else
    src->tail = NULL;
  src->head = last->next;
  src->size -= n;
  last->next = dest->head;
  if (dest->head != NULL)
    dest->head->prev = last;
  else
    dest->tail = last;
  dest->head = first;
  dest->size += n;
}

void		list_move_head_to_tail_all(t_list *src,
					   t_list *dest)
{
  if (src->tail == NULL)
    return ;
  assert(src->tail != NULL && src->head != NULL);
  src->head->prev = dest->tail;
  if (dest->tail != NULL)
    dest->tail->next = src->head;
  else
    dest->head = src->head;
  dest->tail = src->tail;
  dest->size += src->size;
  src->head = src->tail = NULL;
  src->size = 0;
}

void		list_move_head_to_tail(t_list *src,
				       t_list *dest,
				       unsigned int n)
{
  t_elem	*first;
  t_elem	*last;

  assert(src->size >= n);
  first = src->head;
  last = list_get_elem(src, n);
  assert(last != NULL);
  if (last->next != NULL)
    last->next->prev = NULL;
  else
    src->tail = NULL;
  src->head = last->next;
  src->size -= n;
  last->next = NULL;
  first->prev = dest->tail;
  if (dest->tail != NULL)
    dest->tail->next = first;
  else
    dest->head = first;
  dest->tail = last;
  dest->size += n;
}
