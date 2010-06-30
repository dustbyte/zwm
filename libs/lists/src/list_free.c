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
