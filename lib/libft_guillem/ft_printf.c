/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 20:06:05 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 14:06:12 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_format_checker(va_list ap, const char *str, int *length, int i)
{
	if (str[i + 1] == 's')
		ft_print_str(va_arg(ap, char *), length);
	else if (str[i + 1] == 'c')
		ft_put_char(va_arg(ap, int), length);
	else if (str[i + 1] == 'd')
		ft_put_number(va_arg(ap, int), length);
	else if (str[i + 1] == 'i')
		ft_put_number(va_arg(ap, int), length);
	else if (str[i + 1] == 'u')
		ft_put_unsigned(va_arg(ap, unsigned int), length);
	else if (str[i + 1] == 'x')
		ft_put_hex(va_arg(ap, unsigned int), length);
	else if (str[i + 1] == 'X')
		ft_put_hex_mayus(va_arg(ap, unsigned int), length);
	else if (str[i + 1] == 'p')
		ft_print_pointer(va_arg(ap, unsigned long), length);
	else if (str[i + 1] == '%')
		ft_put_char('%', length);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		length;

	i = 0;
	length = 0;
	if (!str)
		return (0);
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			ft_format_checker(ap, str, &length, i);
			i++;
		}
		else
			ft_put_char(str[i], &length);
		if (length == -1)
			return (-1);
		i++;
	}
	va_end(ap);
	return (length);
}
