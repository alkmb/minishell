/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 13:37:52 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/11 18:02:05 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr_n;

	ptr_n = malloc(count * size);
	if (ptr_n == NULL)
		return (NULL);
	ft_bzero(ptr_n, count * size);
	return (ptr_n);
}
