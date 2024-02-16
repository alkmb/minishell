/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/02/16 11:30:31 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parser	initialize_parser(char *commands[], int n)
{
	t_parser	parser;

	parser.j = 0;
	parser.i = 0;
	parser.is_single_quote = 0;
	parser.is_double_quote = 0;
	parser.char_index = 0;
	parser.args = (char **)malloc(MAX_ARGS * sizeof(char *));
	parser.command = commands[n];
	parser.current_token = malloc(1000 * sizeof(char));
	return (parser);
}

void	handle_arg(t_parser *parser)
{
	if (!parser->is_double_quote && parser->char_index != 0)
	{
		parser->current_token[parser->char_index] = '\0';
		parser->args[parser->i++] = ft_strdup(parser->current_token);
		parser->char_index = 0;
	}
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

char	**token_pipe_cmd(char *commands[], int n)
{
	t_parser	parser;

	parser = initialize_parser(commands, n);
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
