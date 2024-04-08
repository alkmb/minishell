/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/04/08 09:53:25 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_arg(t_parser *parser)
{
	if (!parser->is_double_quote && parser->char_index != 0)
	{
		parser->current_token[parser->char_index] = '\0';
		parser->args[parser->i++] = ft_strdup(parser->current_token);
		parser->char_index = 0;
	}
}

int	is_single_quote(char *str, int index)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < index)
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

void	process_command(t_parser *parser)
{
	while (parser->j < ft_strlen(parser->command))
	{
		parser->character = parser->command[parser->j];
		if (parser->character == '\'')
		{
			parser->is_single_quote = !parser->is_single_quote;
			handle_arg(parser);
		}
		else if (parser->character == '\"')
		{
			parser->is_double_quote = !parser->is_double_quote;
			if (!parser->is_double_quote && parser->char_index != 0)
				handle_arg(parser);
		}
		else if ((parser->character == ' ' || parser->character == '\t')
			&& !parser->is_single_quote && !parser->is_double_quote)
		{
			if (parser->char_index != 0)
				handle_arg(parser);
		}
		else
			parser->current_token[parser->char_index++] = parser->character;
		parser->j++;
	}
}

char	**token_pipe_cmd(char	*command[], int i)
{
	t_parser	parser;

	parser = initialize_parser(command, i);
	process_command(&parser);
	if (parser.char_index != 0)
	{
		parser.current_token[parser.char_index] = '\0';
		parser.args[parser.i++] = ft_strdup(parser.current_token);
	}
	parser.args[parser.i] = NULL;
	free(parser.current_token);
	return (parser.args);
}
