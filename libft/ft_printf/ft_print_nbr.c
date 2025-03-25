/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:20:49 by rxue              #+#    #+#             */
/*   Updated: 2024/12/09 17:20:52 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_nbr_len(int nbr)
{
	unsigned int	n;
	int				i;

	i = 0;
	n = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		i++;
		n = (unsigned int)(-nbr);
	}
	else
		n = nbr;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_nbr_to_str(int nbr, char *result)
{
	int				i;
	int				len;
	unsigned int	n;

	i = 0;
	len = ft_nbr_len(nbr);
	if (nbr < 0)
	{
		result[0] = '-';
		n = -nbr;
	}
	else
		n = nbr;
	if (nbr == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	while (n > 0)
	{
		result[len - i - 1] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (result);
}

int	ft_print_nbr(int nbr)
{
	char	*result;
	int		len;
	int		print_length;

	len = ft_nbr_len(nbr);
	print_length = 0;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = '\0';
	result = ft_nbr_to_str(nbr, result);
	print_length = ft_print_str(result);
	free(result);
	return (print_length);
}
