/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 02:18:32 by akambou           #+#    #+#             */
/*   Updated: 2023/11/21 23:45:24 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	check_form(char str, va_list *fmt, int *len, int *i)
{
	int	size;

	size = 0;
	if (str == 'c')
		size = ft_char_len(va_arg(*fmt, int), len);
	else if (str == 's')
		size = ft_str_len(va_arg(*fmt, char *), len);
	else if (str == 'i' || str == 'd')
		size = ft_nbr(va_arg(*fmt, int), len);
	else if (str == 'u')
		size = ft_unsint(va_arg(*fmt, unsigned int), len);
	else if (str == 'p')
		size = ft_ptr(va_arg(*fmt, unsigned long), len);
	else if (str == 'x')
		size = ft_hex(va_arg(*fmt, unsigned int), len, "0123456789abcdef");
	else if (str == 'X')
		size = ft_hex(va_arg(*fmt, unsigned int), len, "0123456789ABCDEF");
	else if (str == '%')
		size = ft_char_len('%', len);
	else
		(*i)--;
	return (size);
}

int	ft_printf(const char *str, ...)
{
	va_list	fmt;
	int		i;
	int		len;

	i = 0;
	len = 0;
	va_start(fmt, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			i++;
			len = check_form(str[i], &fmt, &len, &i);
			if (len == -1)
				return (-1);
		}
		else
		{
			if (ft_char_len((char)str[i], &len) == -1)
				return (-1);
		}
		i++;
	}
	va_end(fmt);
	return (len);
}
