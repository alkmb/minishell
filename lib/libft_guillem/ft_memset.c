/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 23:54:03 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/11 18:31:49 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	char			*pb;
	unsigned char	cc;

	i = 0;
	pb = b;
	cc = c;
	while (i < len)
	{
		pb[i] = cc;
		i++;
	}
	return (pb);
}
