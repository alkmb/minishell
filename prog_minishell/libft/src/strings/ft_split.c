/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 03:02:55 by kmb               #+#    #+#             */
/*   Updated: 2023/12/21 03:07:22 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	count_words(char *s, char c)
{
	int	i;
	int	n_word;
	int	control;

	if (!s) // Check if s is NULL
		return 0;

	i = 0;
	control = 0;
	n_word = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && control == 0)
		{
			control = 1;
			n_word++;
		}
		else if (s[i] == c)
			control = 0;
		i++;
	}
	return (n_word);
}

static char	*string(char *s, int init, int end)
{
	char	*string;
	int		i;

	if (!s) // Check if s is NULL
		return NULL;

	i = 0;
	string = (char *)malloc((end - init + 1) * sizeof(char));
	if (!string) // Check if malloc was successful
		return NULL;

	while (end > init)
	{
		string[i] = s[init];
		i++;
		init++;
	}
	string[i] = '\0';

	return string;
}

char	**ft_split(char *s, char c)
{
	char	**split;
	int		init_w;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (NULL);
	i = -1;
	j = 0;
	init_w = -1;
	split = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (split == 0)
		return (NULL);
	while (++i <= ft_strlen(s))
	{
		if (s[i] != c && init_w < 0)
			init_w = i;
		else if ((s[i] == c || i == ft_strlen(s)) && init_w >= 0)
		{
			split[j++] = string(s, init_w, i);
			init_w = -1;
		}
	}
	split[j] = NULL;
	return (split);
}
