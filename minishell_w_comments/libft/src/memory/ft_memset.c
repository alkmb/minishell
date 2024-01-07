/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:17:07 by akambou           #+#    #+#             */
/*   Updated: 2023/11/22 23:23:17 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
