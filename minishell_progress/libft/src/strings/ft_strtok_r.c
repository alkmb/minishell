/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok_r.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:53:31 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 16:03:25 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
#include <string.h>

char *ft_strtok_r(char *str, const char *delim, char **saveptr)
{
	char *end;

	if (str == NULL)
		str = *saveptr;
	if (*str == '\0')
		return NULL;
	str += ft_strspn(str, delim);
	if (*str == '\0')
		return NULL;
	end = str + ft_strcspn(str, delim);
	if (*end == '\0')
		*saveptr = end;
	else
	{
		*end = '\0';
		*saveptr = end + 1;
	}
	return (str);
}
