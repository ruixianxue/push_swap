/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:23:57 by rxue              #+#    #+#             */
/*   Updated: 2025/03/27 12:56:08 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long	ft_atol(const char *s)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while ((*s >= 9 && *s <= 13) || *s == 32)
		s++;
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		result = result * 10 + (*s++ - '0');
	return (result * sign);
}

static void	append_node(t_stack_node **stack, int n)
{
	t_stack_node	*node;
	t_stack_node	*last_node;

	if (!stack)
		return ;
	node = malloc(sizeof(t_stack_node));
	if (!node)
		return ;
	node->next = NULL;
	node->nbr = n;
	node->cheapest = 0;
	if (!(*stack))
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

static void	free_tmp(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
		free(tmp[i++]);
	free(tmp);
}

void	sub_process_av(char *str, t_stack_node **a)
{
	char			**tmp;
	int				i;
	long			n;

	i = 0;
	tmp = ft_split(str, ' ');
	if (!tmp |!tmp[0])
	{
		free_tmp(tmp);
		ft_error(a);
	}
	while (tmp[i])
	{
		n = ft_atol(tmp[i]);
		if (error_syntax(tmp[i]) || n > INT_MAX || n < INT_MIN)
		{
			free_tmp(tmp);
			ft_error(a);
		}
		append_node(a, (int)n);
		i++;
	}
	free_tmp(tmp);
}

t_stack_node	*process_av(int argc, char **argv)
{
	t_stack_node	*a;
	int				i;
	long			n;

	i = 1;
	a = NULL;
	if (argc < 2)
		exit(0);
	while (i < argc)
	{
		if (find_space(argv[i]))
			sub_process_av(argv[i], &a);
		else
		{
			n = ft_atol(argv[i]);
			if (error_syntax(argv[i]) || n > INT_MAX || n < INT_MIN)
				ft_error(&a);
			append_node(&a, (int)n);
		}
		i++;
	}
	return (a);
}
