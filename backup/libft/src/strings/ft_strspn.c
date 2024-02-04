/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:58:08 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 16:04:34 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t  ft_strspn(char *str, const char *str2)
{
	size_t i;
	char *s2;

	i = 0;
	s2 = (char *)str2;
	while (str[i])
	{
		if (ft_strchr(s2, str[i]) == 0)
			break;
		++i;
	}
	return (i);
}
