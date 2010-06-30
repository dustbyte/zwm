/*
** list_free.c for zappy in /home/mota/projets/tek2/zappy/server/libs/lists/src
**
** Made by pierre wacrenier
** Login   <wacren_p@epitech.net>
**
** Started on  Tue Jun 15 18:17:07 2010 pierre wacrenier
** Last update Thu Jun 17 00:31:53 2010 pierre wacrenier
*/

#include <stdlib.h>
#include <stdio.h>

#include "lists.h"

void		list_free_dfl(void *data)
{
  free(data);
}

void		list_free_fake(void *data)
{
  (void)data;
}
