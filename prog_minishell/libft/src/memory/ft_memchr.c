/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:16:18 by akambou           #+#    #+#             */
/*   Updated: 2023/11/22 23:23:02 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s2;
	unsigned char		c2;

	c2 = c;
	s2 = s;
	while (n > 0)
	{
		if (*s2 == c2)
			return ((unsigned char *)s2);
		s2++;
		n--;
	}
	return (NULL);
}
