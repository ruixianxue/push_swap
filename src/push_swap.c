#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack_node	*a;
	t_stack_node	*b;

	b = NULL;
	a = process_av(argc, argv);
	if (!a || error_duplicate(a))
	{
		ft_free(&a);
		ft_error();
	}
	if (!check_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a, false);
		else if (stack_len(a) == 3)
			sort_three(&a);
		else
			sort_stack(&a, &b);
	}
	ft_free(&a); // where free stack b?
	return (0);
}