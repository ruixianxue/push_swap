/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rxue <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 18:03:04 by rxue              #+#    #+#             */
/*   Updated: 2024/12/06 18:03:07 by rxue             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

int	ft_printf(const char *str, ...);
int	ft_print_char(int c);
int	ft_print_str(char *str);
int	ft_print_hex(unsigned int nbr, const char format);
int	ft_print_ptr(void *ptr);
int	ft_print_nbr(int nbr);
int	ft_print_unsigned(unsigned int nbr);
int	ft_print_percent(void);

#endif
