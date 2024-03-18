/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 00:46:10 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// initialize the parser
void	handle_arg(t_parser *parser)
{
	// if the character is a single quote and not in double quotes
	if (!parser->is_double_quote && parser->char_index != 0)
	{
		// add the token to the args array
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
	// loop through the command
	while (parser->j < ft_strlen(parser->command))
	{
		// get the current character
		parser->character = parser->command[parser->j];
		if (parser->character == '\'')
		{
			// if the character is a single quote and not in double quotes
			parser->is_single_quote = !parser->is_single_quote;
			handle_arg(parser);
		}
		else if (parser->character == '\"')
		{
			// if the character is a double quote and not in single quotes
			parser->is_double_quote = !parser->is_double_quote;
			if (!parser->is_double_quote && parser->char_index != 0)
				handle_arg(parser);
		}
		else if ((parser->character == ' ' || parser->character == '\t')
			&& !parser->is_single_quote && !parser->is_double_quote)
		{
			// if the character is a space or tab and not in single or double quotes
			if (parser->char_index != 0)
				handle_arg(parser);
		}
		else
			// add the character to the current token
			parser->current_token[parser->char_index++] = parser->character;
		parser->j++;
	}
}

char	**token_pipe_cmd(char *commands[], int n)
{
	t_parser	parser;

	parser = initialize_parser(commands, n);
	process_command(&parser);
	// add the last token to the args array
	if (parser.char_index != 0)
	{
		parser.current_token[parser.char_index] = '\0';
		parser.args[parser.i++] = ft_strdup(parser.current_token);
	}
	parser.args[parser.i] = NULL;
	// free the current token
	free(parser.current_token);
	return (parser.args);
}
