/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:23:38 by rxue              #+#    #+#             */
/*   Updated: 2025/03/25 17:30:25 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate_both(t_stack_node **a, t_stack_node **b, \
							t_stack_node *cheapest_node)
{
	while (*a != cheapest_node->target_node && *b != cheapest_node)
		rr(a, b, false);
	current_index(*a);
	current_index(*b);
}

static void	rev_rotate_both(t_stack_node **a, t_stack_node **b, \
							t_stack_node *cheapest_node)
{
	while (*a != cheapest_node->target_node && *b != cheapest_node)
		rrr(a, b, false);
	current_index(*a);
	current_index(*b);
}

static void	move_a_to_b(t_stack_node **a, t_stack_node **b, int size)
{
	int	len;

	len = stack_len(*a);
	if ((*a)->nbr_index >= size / 2 || len <= size / 2)
		pb(b, a, false);
	else
		ra(a, false);
}

static void	move_b_to_a(t_stack_node **a, t_stack_node **b)
{
	t_stack_node	*cheapest_node;

	cheapest_node = get_cheapest(*b);
	if (cheapest_node->above_median && \
			cheapest_node->target_node->above_median)
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_median) && \
				!(cheapest_node->target_node->above_median))
		rev_rotate_both(a, b, cheapest_node);
	prep_for_push(a, cheapest_node->target_node, 'a');
	prep_for_push(b, cheapest_node, 'b');
	pa(a, b, false);
}

void	sort_stack(t_stack_node **a, t_stack_node **b)
{
	int	size;

	size = stack_len(*a);
	init_nodes_a(*a);
	while (stack_len(*a) > 3 && !check_sorted(*a))
	{
		move_a_to_b(a, b, size);
	}
	sort_three(a);
	while (*b)
	{
		init_nodes_b(*a, *b);
		move_b_to_a(a, b);
	}
	current_index(*a);
	min_on_top(a);
}
