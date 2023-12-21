/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 03:46:47 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/11 16:16:34 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dd;
	const char	*ss;

	i = 0;
	dd = dst;
	ss = src;
	if (dd == 0 && ss == 0)
		return (NULL);
	while (i < n)
	{
		dd[i] = ss[i];
		i++;
	}
	return (dst);
}
