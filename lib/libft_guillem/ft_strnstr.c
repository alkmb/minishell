/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 17:54:28 by gprada-t          #+#    #+#             */
/*   Updated: 2023/09/11 18:35:29 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	if (!needle[i])
		return ((char *)&haystack[i]);
	while (haystack[i])
	{
		j = 0;
		while (haystack[i + j] == needle[j] && (i + j) < len)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <strings.h>

int main()
{
	const char *strlong = "Hola la FF conchasu mare hijueputa";
	const char *strshort = "FF";

	char* ptr = ft_strnstr(strlong, strshort,15);

	printf("%s\n", ptr);

	return (0);
}*/
