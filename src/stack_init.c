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
	if ((result * sign) > INT_MAX || (result * sign < INT_MIN))
		ft_error();
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

t_stack_node	*sub_process_av(char **argv)
{
	t_stack_node	*a;
	char 			**tmp;
	int				i;
	int				n;

	a = NULL;
	i = 0;
	tmp = ft_split(argv[1], ' ');
	while (tmp[i])
	{
		if (error_syntax(tmp[i]))
		{
			ft_free(&a);
			ft_error();
		}	
		n = ft_atol(tmp[i]);
		append_node(a, (int)n)
		i++;
	}
	return (a);
}

t_stack_node	*process_av(int argc, char **argv)
{
	t_stack_node	*a;
	int				i;
	int				n;

	i = 1;
	a = NULL;
	if (argc < 2)
		ft_error();
	else if (argc == 2)
		a = sub_process_av(argv);
	else
	{
		while (i < argc)
		{
			if (error_syntax(tmp[i]))
			{
				ft_free(&a);
				ft_error();
			}
			n = ft_atol(argv[i]);
			append_node(a, (int)n);
		}
	}
	return (a);
}