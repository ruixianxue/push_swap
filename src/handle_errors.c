#include "push_swap.h"

int	error_syntax(char *str)
{
	if (!(*str == '+' || *str == '-' || \
		(*str >= '0' && *str <= '9')))
		return (1);
	if ((*str == '+' || *str = '-') && \
		!(str[1] >= '0' && str[i] <= '9'))
		return (1);
	while (*++str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (1);
	}
	return (0);
}

int	error_duplicate(t_stack_node *a)
{
	t_stack_node	*tmp;
	
	while (a)
	{
		tmp = a->next;
		while (tmp)
		{
			if (a->nbr == tmp->nbr)
				return (1);
			tmp = tmp->next;
		}
		a = a->next;
	}
	return (0);
}

void	ft_free(t_stack_node **stack)
{
	t_stack_node	*tmp;

	if (!stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		(*stack)->nbr = 0;
		free(*stack);
		*stack = tmp;
	}
}

void	ft_error(void)
{
	write(2, "Error\n", 6);
	exit(1);
}