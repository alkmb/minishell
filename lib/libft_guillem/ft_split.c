/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:17:38 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/18 10:29:11 by gpradat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words++;
		while (*s && *s != c)
			s++;
	}
	return (words);
}

static size_t	word_length(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

static char	*words_of_string(char const *s, size_t start, size_t word_length)
{
	char	*words_of_string;

	words_of_string = malloc(sizeof(char) * (word_length + 1));
	if (!words_of_string)
		return (NULL);
	while (start < word_length)
	{
		words_of_string[start] = s[start];
		start++;
	}
	words_of_string[start] = '\0';
	return (words_of_string);
}

static char	**words_array(char const *s, size_t n_words, char c, char **w_array)
{
	size_t	i;
	char	*string;

	i = 0;
	while (i < n_words)
	{
		while (*s == c && *s)
			s++;
		string = (char *)s;
		while (*s != c && *s)
			s++;
		w_array[i] = words_of_string(string, 0, word_length(string, c));
		if (!w_array[i])
		{
			while (i > 0)
				free(w_array[--i]);
			free(w_array);
			return (NULL);
		}
		i++;
	}
	w_array[i] = (NULL);
	return (w_array);
}

char	**ft_split(char const *s, char c)
{
	char	**w_array;
	size_t	n_words;

	w_array = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!w_array)
		return (NULL);
	n_words = count_words(s, c);
	w_array = words_array(s, n_words, c, w_array);
	return (w_array);
}
/*
int main()
{
	char **strings;
	char *string = "Hola que tal como estas";

	int i = 0;
	strings = ft_split(string, ' ');
	while(strings[i])
	{
		printf("%s\n", strings[i]);
		free(strings[i]);
		i++;
	}
	free(strings);
	return (0);
}*/
