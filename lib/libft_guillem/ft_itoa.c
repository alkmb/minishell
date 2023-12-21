/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 04:34:55 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/13 12:50:04 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_len(int n)
{
	int				len;
	long long int	temp;

	len = 0;
	temp = n;
	if (n < 0)
	{
		len++;
		temp = -(long long int)n;
	}
	if (temp == 0)
		len = 1;
	else
	{
		while (temp > 0)
		{
			temp /= 10;
			len++;
		}
	}
	return (len);
}

static void	itoa1(char *str, int n, int len)
{
	long long int	temp;

	temp = n;
	if (n < 0)
	{
		str[0] = '-';
		temp = -(long long int)n;
	}
	str[len] = '\0';
	if (temp == 0)
		str[0] = '0';
	else
	{
		while (temp > 0)
		{
			len--;
			str[len] = (char)((temp % 10) + '0');
			temp /= 10;
		}
	}
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = get_len(n);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	itoa1(str, n, len);
	return (str);
}
