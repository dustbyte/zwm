#ifndef		LISTS_H_
# define	LISTS_H_

typedef enum	e_cmp
  {
    GREATER = 1,
    LESSER
  }		t_cmp;

typedef struct	s_elem
{
  void		*data;
  struct s_elem	*next;
  struct s_elem	*prev;
}		t_elem;

typedef struct	s_list
{
  size_t	size;
  t_elem	*head;
  t_elem	*tail;
}		t_list;

# define	list_foreach(head, elem)			\
for ((elem) = (head); ((elem) != NULL); (elem) = (elem)->next)

# define	list_foreach_as(h, e, c, r)		\
for ((e) = (h); (((e) != NULL) && ((r) = (c((e)->data)))); (e) = (e)->next)

/*
** list_deletion.c
*/

t_elem		*list_remove(t_list *list, t_elem *elem);
int		list_delete(t_list *list, t_elem *self,
			    void (*free_func)(void *data));
void		list_empty(t_list *list, void (*free_func)(void *data));

/*
** list_elem.c
*/

void		elem_push_back(t_list *list, t_elem *self,
			       t_elem *prev, void *data);
void		elem_push_front(t_list *list, t_elem *self,
				t_elem *next, void *data);

/*
** list_insertion.c
*/

void		list_add_head(t_list *list, t_elem *elem, void *data);
void		list_add_tail(t_list *list, t_elem *elem, void *data);
void		list_insert(t_list *list,
			    t_elem *self,
			    void *data,
			    int (*cmp_func)(void *data1, void *data2));

/*
** list_move.c
*/

void		list_move_head_to_head_all(t_list *src, t_list *dest);
void		list_move_head_to_head(t_list *src, t_list *dest,
				       unsigned int n);
void		list_move_head_to_tail_all(t_list *src, t_list *dest);
void		list_move_head_to_tail(t_list *src, t_list *dest,
				       unsigned int n);

/*
** list_search.c
{*/

t_elem		*list_find_elem(t_list *list, void *data);
t_elem		*list_get_elem(t_list *list, size_t iter);

/*
** list_swap.c
*/

int		elem_swap_next(t_elem *elem);
int		elem_swap_prev(t_elem *elem);

/*
** lists.c
*/

void		list_show(t_list *head, void (*show_func)(void *data));
void		list_init(t_list *list);

/*
** list_free.c
*/

void		list_free_dfl(void *data);
void		list_free_fake(void *data);

#endif		/* !LISTS_H_ */
