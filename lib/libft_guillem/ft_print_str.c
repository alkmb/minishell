/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 21:43:56 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 14:05:55 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_char(int c, int *len)
{
	if (write(1, &c, 1) == -1)
		*len = -1;
	else
		(*len)++;
}

void	ft_print_str(char *s, int *len)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		ft_print_str("(null)", len);
		return ;
	}
	while (s[i])
	{
		ft_put_char(s[i], len);
		if (*len == -1)
			return ;
		i++;
	}
}

void	ft_put_hex(unsigned long n, int *len)
{
	char	*base;

	base = "0123456789abcdef";
	if (n > 15)
	{
		ft_put_hex(n / 16, len);
		if (*len == -1)
			return ;
		ft_put_hex(n % 16, len);
		if (*len == -1)
			return ;
	}
	else
	{
		ft_put_char(base[n % 16], len);
		if (*len == -1)
			return ;
	}
}

void	ft_put_hex_mayus(unsigned int n, int *len)
{
	char	*basehex;

	basehex = "0123456789ABCDEF";
	if (n > 15)
	{
		ft_put_hex_mayus(n / 16, len);
		if (*len == -1)
			return ;
		ft_put_hex_mayus(n % 16, len);
		if (*len == -1)
			return ;
	}
	else
	{
		ft_put_char(basehex[n % 16], len);
		if (*len == -1)
			return ;
	}
}
