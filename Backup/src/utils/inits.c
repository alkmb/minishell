/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:14:07 by akambou           #+#    #+#             */
/*   Updated: 2024/04/13 02:12:04 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_command(t_command_data *command)
{
	command->i = 0;
	command->j = 0;
	command->is_malloced[0] = 0;
}

void	initialize_parser(t_shell *shell)
{
	shell->parser->j = 0;
	shell->parser->i = 0;
	shell->parser->is_single_quote = 0;
	shell->parser->is_double_quote = 0;
	shell->parser->char_index = 0;
	shell->parser->args = (char **)malloc(MAX_ARGS * sizeof(char *));
	shell->parser->command = shell->command->commands[shell->data->i];
	shell->parser->current_token = malloc(1000 * sizeof(char));
}
void	initialize_shell(t_shell *shell)
{
	extern char	**environ;
	
	shell->input = NULL;
	shell->prompt = NULL;
	shell->status = 0;
	shell->environ = environ;
	shell->command = malloc(sizeof(t_command_data));
	shell->data = malloc(sizeof(t_pipe_data));
	shell->parser = malloc(sizeof(t_parser));
}