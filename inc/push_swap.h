/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:31:03 by rxue              #+#    #+#             */
/*   Updated: 2025/03/25 17:32:12 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdbool.h>
# include <limits.h>
# include <stdio.h>
# include "../libft/inc/ft_printf.h"
# include "../libft/inc/libft.h"

typedef struct s_stack_node
{
	int					nbr;
	int					index;
	int					nbr_index;
	int					push_cost;
	bool				above_median;
	bool				cheapest;
	struct s_stack_node	*target_node;
	struct s_stack_node	*next;
	struct s_stack_node	*prev;
}	t_stack_node;

//Handle errors
int				error_syntax(char *str);
int				error_duplicate(t_stack_node *a);
void			ft_free(t_stack_node **stack);
void			ft_error(t_stack_node **stack);

//Stack initiation
t_stack_node	*process_av(int argc, char **argv);
void			sub_process_av(char *str, t_stack_node **a);

//Nodes initiation
void			init_nodes_a(t_stack_node *a);
void			init_nodes_b(t_stack_node *a, t_stack_node *b);
void			current_index(t_stack_node *stack);
void			set_cheapest(t_stack_node *stack);
t_stack_node	*get_cheapest(t_stack_node *stack);
void			prep_for_push(t_stack_node **stack, t_stack_node *head, \
						char stack_name);

//Stack utils
int				stack_len(t_stack_node *stack);
int				check_sorted(t_stack_node *stack);
t_stack_node	*find_last(t_stack_node *stack);
t_stack_node	*find_max(t_stack_node *stack);
t_stack_node	*find_min(t_stack_node *stack);
void			min_on_top(t_stack_node **a);
void			value_index(t_stack_node *head);
int				find_space(char *str);

//Commands
void			pa(t_stack_node **a, t_stack_node **b);
void			pb(t_stack_node **b, t_stack_node **a);
void			sa(t_stack_node **a);
void			sb(t_stack_node **b);
void			ss(t_stack_node **a, t_stack_node **b);
void			ra(t_stack_node **a);
void			rb(t_stack_node **b);
void			rr(t_stack_node **a, t_stack_node **b);
void			rra(t_stack_node **a);
void			rrb(t_stack_node **b);
void			rrr(t_stack_node **a, t_stack_node **b);

//Algrithms
void			sort_three(t_stack_node **a);
void			sort_stack(t_stack_node **a, t_stack_node **b);

#endif
