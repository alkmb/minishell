/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_numbers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 00:33:36 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 14:05:26 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	recursive_put_number(int n, int *len)
{
	if (n > 9)
	{
		ft_put_number(n / 10, len);
		if (*len == -1)
			return ;
		ft_put_number(n % 10, len);
		if (*len == -1)
			return ;
	}
	else
	{
		ft_put_char(n % 10 + 48, len);
		if (*len == -1)
			return ;
	}
}

void	ft_put_number(int n, int *len)
{
	if (n == -2147483648)
	{
		ft_print_str("-2147483648", len);
		return ;
	}
	if (n < 0)
	{
		ft_put_char('-', len);
		if (*len == -1)
			return ;
		n = n * -1;
	}
	recursive_put_number(n, len);
}

void	ft_put_unsigned(unsigned int n, int *len)
{
	if (n > 9)
	{
		ft_put_unsigned(n / 10, len);
		if (*len == -1)
			return ;
		ft_put_unsigned(n % 10, len);
		if (*len == -1)
			return ;
	}
	else
	{
		ft_put_char(n % 10 + 48, len);
		if (*len == -1)
			return ;
	}
}
