#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include "ft_printf.h"
# include "../libft/libft.h"

typedef struct s_stack_node
{
	int					nbr;
	int					index;
	int					push_cost;
	bool				above_median;
	bool				cheapest;
	struct s_stack_node *tsrget_node;
	struct s_stack_node	*next;
	struct s_stack_node *prev;
}	t_stack_node;

//Handle errors

//Stack initiation

//Nodes initiation

//Stack utils

//Commands

//Algrithms

#endif