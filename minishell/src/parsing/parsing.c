/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/04/08 10:58:19 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_commands(t_command_data *command)
{
	int j = 0;
	
	while (command->commands[command->i][j] != '\0')
	{
		if (command->commands[command->i][j] == '$'
			&& command->commands[command->i][j + 1] != '?'
			&& (is_single_quote(command->commands[command->i], j) == 0))
			handle_variable_expansion(command->commands, &j, \
				command->is_malloced, command->var_name);
		else
			j++;
	}

}

void	chose_command(t_command_data *command, t_commandhistory *history)
{
	t_pipe_data	data;

	command->i -= 1;
	if (command->i < 0)
		return ;
	else
	{
		initialize_variables(&data.i, &data.fd_in);
		chose_pipe(command->commands, command->i, history);
		return ;
	}
}

void	parse_command(char *input, t_commandhistory *history)
{
	t_command_data		command;

	initialize_command_data(&command);
	add_to_history(history, input);
	if (handle_exception(input) == 0)
		return ;
	command.commands[command.i] = ft_strtok(input, "|");
	while (command.commands[command.i] != NULL)
	{
		handle_commands(&command);
		command.i++;
		command.commands[command.i] = ft_strtok(NULL, "|");
	}
	chose_command(&command, history);
}
