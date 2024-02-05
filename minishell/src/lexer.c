/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/02/05 04:42:58 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**token_pipe_cmd(char *commands[], int n)
{
	int		j = 0;
	int		i = 0;
	char	**args = (char **)malloc(MAX_ARGS * sizeof(char*));
	char	*command = commands[n];
	char	*current_token = malloc(1000 * sizeof(char));
	int		is_single_quote = 0;
	int		is_double_quote = 0;
	int		char_index = 0;
	char	character;

	while (j < ft_strlen(command))
	{
		character = command[j];
		if (character == '\'')
		{
			is_single_quote = !is_single_quote;
			if (!is_single_quote && char_index != 0)
			{
				current_token[char_index] = '\0';
				args[i++] = ft_strdup(current_token);
				char_index = 0;
			}
		}
		else if (character == '\"')
		{
			is_double_quote = !is_double_quote;
			if (!is_double_quote && char_index != 0)
			{
				current_token[char_index] = '\0';
				args[i++] = ft_strdup(current_token);
				char_index = 0;
			}
		}
		else if ((character == ' ' || character == '\t')
			&& !is_single_quote && !is_double_quote)
		{
			if (char_index != 0)
			{
				current_token[char_index] = '\0';
				args[i++] = ft_strdup(current_token);
				char_index = 0;
			}
		}
		else
			current_token[char_index++] = character;
		j++;
	}
	if (char_index != 0)
	{
		current_token[char_index] = '\0';
		args[i++] = ft_strdup(current_token);
	}
	args[i] = NULL;
	free(current_token);
	return (args);
}