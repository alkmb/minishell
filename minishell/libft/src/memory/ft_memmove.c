/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:16:53 by akambou           #+#    #+#             */
/*   Updated: 2023/11/22 23:23:14 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
