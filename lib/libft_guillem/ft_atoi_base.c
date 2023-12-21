/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:46:04 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/29 15:53:45 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test_base(const char c)
{
	int	nb;

	if (c >= '0' && c <= '9')
		nb = c - '0';
	if (c >= 'a' && c <= 'z')
		nb = c - 'a' + 10;
	if (c >= 'A' && c <= 'Z')
		nb = c - 'A' + 10;
	else
		nb = -1;
	return (nb);
}

int			ft_atoi_base(const char *str, int base)
{
	int		i;
	int		sign;
	int		nb;
	int		current;

	i = 0;
	nb = 0;
	sign = 1;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	current = test_base(str[i]);
	while (current >= 0 && current < base)
	{
		nb = nb * base + current;
		i++;
		current = test_base(str[i]);
	}
	return (sign * nb);
}
