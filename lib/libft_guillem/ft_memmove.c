/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 14:36:11 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/18 10:28:36 by gpradat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*dst2;
	const char	*src2;

	dst2 = dst;
	src2 = src;
	if (dst2 == 0 && src2 == 0)
		return (NULL);
	if (dst2 > src2)
	{
		while (len)
		{
			len--;
			dst2[len] = src2[len];
		}
	}
	else
		ft_memcpy(dst2, src2, len);
	return (dst2);
}
