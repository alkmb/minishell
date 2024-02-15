/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/02/15 05:52:20 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_str(char **args, int i, int char_index, char *current_token)
{
	current_token[char_index] = '\0';
	args[i++] = ft_strdup(current_token);
	char_index = 0;
}

char	**token_pipe_cmd(char *commands[], int n)
{
	int		j;
	int		i;
	int		is_single_quote;
	int		is_double_quote;
	int		char_index;
	char	character;
	char	**args;
	char	*command;
	char	*current_token;

	j = 0;
	i = 0;
	is_single_quote = 0;
	is_double_quote = 0;
	char_index = 0;
	args = (char **)malloc(MAX_ARGS * sizeof(char *));
	command = commands[n];
	current_token = malloc(1000 * sizeof(char));
	while (j < ft_strlen(command))
	{
		character = command[j];
		if (character == '\'')
		{
			is_single_quote = !is_single_quote;
			if (!is_double_quote && char_index != 0)
				dup_str(args, i, char_index, current_token);
		}
		else if (character == '\"')
		{
			is_double_quote = !is_double_quote;
			if (!is_double_quote && char_index != 0)
				dup_str(args, i, char_index, current_token);
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
