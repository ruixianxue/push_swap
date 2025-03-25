/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:21:20 by rxue              #+#    #+#             */
/*   Updated: 2024/12/09 17:21:22 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_ptr_len(unsigned long long nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		i++;
	while (nbr > 0)
	{
		nbr /= 16;
		i++;
	}
	return (i);
}

void	ft_put_ptr(unsigned long long nbr)
{
	if (nbr >= 16)
	{
		ft_put_ptr(nbr / 16);
		ft_put_ptr(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_print_char(nbr + '0');
		else
			ft_print_char(nbr - 10 + 'a');
	}
}

int	ft_print_ptr(void *ptr)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	write(1, "0x", 2);
	ft_put_ptr((unsigned long long)ptr);
	return (ft_ptr_len((unsigned long long)ptr) + 2);
}
