/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:20:35 by rxue              #+#    #+#             */
/*   Updated: 2024/12/09 17:20:38 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_hex_len(unsigned int nbr)
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

void	ft_put_hex(unsigned int nbr, const char format)
{
	if (nbr >= 16)
	{
		ft_put_hex(nbr / 16, format);
		ft_put_hex(nbr % 16, format);
	}
	else
	{
		if (nbr <= 9)
			ft_print_char(nbr + '0');
		else
		{
			if (format == 'x')
				ft_print_char(nbr - 10 + 'a');
			if (format == 'X')
				ft_print_char(nbr - 10 + 'A');
		}
	}
}

int	ft_print_hex(unsigned int nbr, const char format)
{
	ft_put_hex(nbr, format);
	return (ft_hex_len(nbr));
}
