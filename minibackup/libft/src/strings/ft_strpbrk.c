/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpbrk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 14:12:07 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 15:15:55 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char *ft_strpbrk(const char *str, const char *accept) {
	while (*str) {
		const char *a = accept;
		while (*a) {
			if (*a++ == *str)
				return (char *)str;
		}
		str++;
	}
	return NULL;
}
