#include "push_swap.h"

static void	rev_rotate(t_stack_node **head)
{
	t_stack_node	*last_node;

	if (!*head || !(*head)->next)
		return ;
	last_node = find_last(*head);
	last_node->prev->next = NULL;
	last_node->next = *head;
	last_node->prev = NULL;
	*head = last_node;
	last_node->next->prev = last_node;
}

void	rra(t_stack_node **a, bool print)
{
	rev_rotate(a);
	if (!print)
		ft_printf("rra\n");
}

void	rrb(t_stack_node **b, bool print)
{
	rev_rotate(b);
	if (!print)
		ft_printf("rrb\n");
}

void	rrr(t_stack_node **a, bool print)
{
	rev_rotate(a);
	rev_rotate(b);
	if (!print)
		ft_printf("rrr\n");
}