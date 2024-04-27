/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:09:29 by kmb               #+#    #+#             */
/*   Updated: 2024/02/05 00:24:48 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*src = NULL;
	char		*p;
	char		*ret;

	ret = NULL;
	if (str != NULL)
		src = str;
	if (src == NULL)
		return (NULL);
	p = ft_strpbrk(src, delim);
	if (p != NULL)
	{
		*p = 0;
		ret = src;
		src = ++p;
	}
	else if (*src)
	{
		ret = src;
		src = NULL;
	}
	return (ret);
}
