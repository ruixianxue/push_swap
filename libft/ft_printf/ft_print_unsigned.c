/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <rxue@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 17:22:23 by rxue              #+#    #+#             */
/*   Updated: 2024/12/09 17:22:24 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

int	ft_unbr_len(unsigned int nbr)
{
	int				i;

	i = 0;
	if (nbr == 0)
		i++;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_unbr_to_str(unsigned int nbr, char *result)
{
	int				i;
	int				len;

	i = 0;
	len = ft_unbr_len(nbr);
	if (nbr == 0)
	{
		result[0] = '0';
		result[1] = '\0';
	}
	while (nbr > 0)
	{
		result[len - i - 1] = (nbr % 10) + '0';
		nbr /= 10;
		i++;
	}
	return (result);
}

int	ft_print_unsigned(unsigned int nbr)
{
	char	*result;
	int		len;
	int		print_length;

	len = ft_unbr_len(nbr);
	print_length = 0;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (0);
	result[len] = '\0';
	result = ft_unbr_to_str(nbr, result);
	print_length = ft_print_str(result);
	free(result);
	return (print_length);
}
