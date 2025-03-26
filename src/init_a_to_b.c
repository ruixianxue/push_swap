/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_a_to_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:24:29 by rxue              #+#    #+#             */
/*   Updated: 2025/03/25 17:24:32 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	current_index(t_stack_node *stack)
{
	int	i;
	int	median;

	i = 0;
	if (!stack)
		return ;
	median = stack_len(stack) / 2;
	while (stack)
	{
		stack->index = i;
		if (i <= median)
			stack->above_median = true;
		else
			stack->above_median = false;
		stack = stack->next;
		i++;
	}
}

static void	sort_node_array(t_stack_node *node_array[], int len)
{
	int				i;
	int				j;
	t_stack_node	*tmp;

	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (node_array[j]->nbr > node_array[j + 1]->nbr)
			{
				tmp = node_array[j];
				node_array[j] = node_array[j + 1];
				node_array[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	value_index(t_stack_node *head)
{
	t_stack_node	**node_array;
	t_stack_node	*tmp;
	int				i;
	int				len;

	len = stack_len(head);
	node_array = (t_stack_node **)malloc(len * sizeof (t_stack_node *));
	if (!node_array)
		return ;
	tmp = head;
	i = 0;
	while (i < len)
	{
		node_array[i++] = tmp;
		tmp = tmp->next;
	}
	sort_node_array(node_array, len);
	i = 0;
	while (i < len)
	{
		node_array[i]->nbr_index = i;
		i++;
	}
	free(node_array);
}

void	init_nodes_a(t_stack_node *a)
{
	current_index(a);
	value_index(a);
}
