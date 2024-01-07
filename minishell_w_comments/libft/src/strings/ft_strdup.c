/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:17:28 by akambou           #+#    #+#             */
/*   Updated: 2023/11/23 00:06:45 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

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
