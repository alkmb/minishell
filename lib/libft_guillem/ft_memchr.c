/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:47:57 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/11 17:17:57 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
