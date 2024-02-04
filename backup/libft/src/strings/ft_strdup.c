/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 22:17:28 by akambou           #+#    #+#             */
/*   Updated: 2024/01/21 05:39:18 by kmb              ###   ########.fr       */
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
