/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 19:30:29 by alkmb             #+#    #+#             */
/*   Updated: 2023/11/21 23:44:41 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_nbr_recursive(int nbr, int *len)
{
	if (nbr > 9)
	{
		if (ft_nbr(nbr / 10, len) == -1)
			return (-1);
		if (ft_char_len(nbr % 10 + '0', len) == -1)
			return (-1);
	}
	else
	{
		if (ft_char_len(nbr + '0', len) == -1)
			return (-1);
	}
	return (*len);
}

int	ft_nbr(int nbr, int *len)
{
	if (nbr == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		(*len) += 11;
		return (*len);
	}
	if (nbr < 0)
	{
		if (ft_char_len('-', len) == -1)
			return (-1);
		nbr = nbr * -1;
	}
	return (ft_nbr_recursive(nbr, len));
}

int	ft_ptr(unsigned long ptr, int *len)
{
	char	str[25];
	int		i;
	char	*base;

	i = 0;
	base = "0123456789abcdef";
	if (write (1, "0x", 2) == -1)
		return (-1);
	(*len) += 2;
	if (ptr == 0)
	{
		if (ft_char_len('0', len) == -1)
			return (-1);
		return (*len);
	}
	while (ptr != 0)
	{
		str[i] = base[ptr % 16];
		ptr = ptr / 16;
		i++;
	}
	while (i--)
		if (ft_char_len(str[i], len) == -1)
			return (-1);
	return (*len);
}

int	ft_hex(unsigned int nbr, int *len, const char *base)
{
	char	str[25];
	int		i;

	i = 0;
	if (nbr == 0)
	{
		if (ft_char_len('0', len) == -1)
			return (-1);
		return (*len);
	}
	while (nbr != 0)
	{
		str[i] = base[nbr % 16];
		nbr = nbr / 16;
		i++;
	}
	while (i--)
	{
		if (ft_char_len(str[i], len) == -1)
			return (-1);
	}
	return (*len);
}

int	ft_unsint(unsigned int nbr, int *len)
{
	if (nbr > 9)
	{
		if (ft_unsint(nbr / 10, len) == -1)
			return (-1);
		if (ft_char_len(nbr % 10 + '0', len) == -1)
			return (-1);
	}
	else if (ft_char_len(nbr + '0', len) == -1)
		return (-1);
	return (*len);
}
