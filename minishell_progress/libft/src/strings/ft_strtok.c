/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:09:29 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 14:14:35 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char *ft_strtok(char *str, char *delim)
{
	static char *src = NULL;
	char *p, *ret = 0;

	if(str != NULL)
		src = str;

	if(src == NULL)
		return NULL;

	if((p = ft_strpbrk(src, delim)) != NULL) {
		*p  = 0;
		ret = src;
		src = ++p;
	}
	else if(*src) {
		ret = src;
		src = NULL;
	}

	return ret;
}
