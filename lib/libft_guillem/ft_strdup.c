/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 18:53:04 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/12 19:40:48 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*new;
	int		size;

	size = 0;
	while (str[size])
		size++;
	new = malloc((size + 1) * sizeof(char));
	if (!new)
		return (NULL);
	size = 0;
	while (str[size])
	{
		new[size] = str[size];
		size++;
	}
	new[size] = '\0';
	return (new);
}
