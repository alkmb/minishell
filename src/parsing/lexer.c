/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 07:25:30 by kmb               #+#    #+#             */
/*   Updated: 2024/04/17 09:43:36 by gprada-t         ###   ########.fr       */
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

char	**token_pipe_cmd(t_shell *shell)
{
	initialize_parser(shell);
	process_command(shell->parser);
	if (shell->parser->char_index != 0)
	{
		shell->parser->current_token[shell->parser->char_index] = '\0';
		shell->parser->args[shell->parser->i++] = \
		ft_strdup(shell->parser->current_token);
	}
	shell->parser->args[shell->parser->i] = NULL;
	free(shell->parser->current_token);
	return (shell->parser->args);
}

void	chose_command(t_shell *shell)
{
	shell->command->i -= 1;
	if (shell->command->i < 0)
		return ;
	else
	{
		shell->data->i = 0;
		shell->data->fd_in = 0;
		chose_pipe(shell);
	}
}
