/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 13:26:05 by gprada-t          #+#    #+#             */
/*   Updated: 2023/11/17 18:23:51 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*free_buffer(char **buffer)
{
	free(*buffer);
	*buffer = NULL;
	return (NULL);
}

size_t	ft_strlen_protect(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strchr_gnl(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return (s);
		s++;
	}
	if (*s == (char)c)
		return (s);
	return (NULL);
}

char	*ft_join_and_free_gnl(char *buffer, char *temp)
{
	char	*result;
	size_t	buff_len;
	size_t	temp_len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	buff_len = ft_strlen_protect(buffer);
	temp_len = ft_strlen_protect(temp);
	result = malloc((buff_len + temp_len + 1) * sizeof(char));
	if (!result)
		return (free_buffer(&buffer));
	while (buffer && i < buff_len && *buffer != '\n')
	{
		result[i] = buffer[i];
		i++;
	}
	while (temp && j < temp_len)
		result[i++] = temp[j++];
	result[i] = '\0';
	free_buffer(&buffer);
	return (result);
}

char	*ft_substr_gnl(char *str, unsigned int start, size_t len)
{
	char	*substr;
	size_t	str_len;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	str_len = ft_strlen_protect(str);
	if (str_len < len)
		len = str_len;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (str[start] && (i < len))
		substr[i++] = str[start++];
	substr[i] = '\0';
	return (substr);
}
