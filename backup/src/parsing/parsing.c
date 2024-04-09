/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/04/09 04:44:43 by akambou          ###   ########.fr       */
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
			&& (is_single_quote(command->commands[command->i], \
			j) == 0))
			handle_variable_expansion(command->commands, &j, \
				command->is_malloced, command->var_name);
		else
			j++;
	}
}

int	chose_command(t_command_data *command, t_commandhistory *history)
{
	t_pipe_data	data;

	command->i -= 1;
	if (command->i < 0)
		return (0);
	else
	{
		initialize_variables(&data.i, &data.fd_in);
		data.status = chose_pipe(command, &data, history);
		return (data.status);
	}
	return (data.status);
}

int	parse_command(char *input, t_commandhistory *history)
{
	t_command_data		command;
	int					status;

	initialize_command_data(&command);
	add_to_history(history, input);
	if (handle_exception(input) == 0)
		return (0);
	command.commands[command.i] = ft_strtok(input, "|");
	while (command.commands[command.i] != NULL)
	{
		handle_commands(&command);
		command.i++;
		command.commands[command.i] = ft_strtok(NULL, "|");
	}
	status = chose_command(&command, history);
	return (status);
}
