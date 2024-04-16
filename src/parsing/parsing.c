/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/04/17 00:57:16 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var_name_and_value(t_command_data *command)
{
	command->var_name_len = 0;
	while (ft_isalnum(command->commands[command->i][command->j]) 
	|| command->commands[command->i][command->j] == '_')
		command->var_name[command->var_name_len++] = command->commands[command->i][(command->j)++];
	command->var_name[command->var_name_len] = '\0';
	return (getenv(command->var_name));
}

void	handle_variable_expansion(t_command_data *command)
{
	command->j++;
	command->var_value = get_var_name_and_value(command);
	if (command->var_value != NULL && ft_strlen(command->var_value) >= ft_strlen(command->var_name))
	{
		command->var_name_len = ft_strlen(command->var_name);
		command->new_command = malloc((ft_strlen(command->commands[command->i]) - \
		command->var_name_len + ft_strlen(command->var_value)) * sizeof(char));
		ft_strlcpy(command->new_command, command->commands[command->i], command->j);
		ft_strlcpy(command->new_command + command->j - command->var_name_len - 1, \
		command->var_value, ft_strlen(command->var_value));
		free_malloced(command->commands, command->is_malloced ,command->i);
		command->commands[command->i] = command->new_command;
		command->is_malloced[command->i] = 1;
	}
	else if (command->var_value != NULL && ft_strlen(command->var_value) < ft_strlen(command->var_name))
	{
		command->var_name_len = ft_strlen(command->var_name);
		command->new_command = ft_strdup(command->commands[command->i]);
		ft_strlcpy(command->new_command, command->commands[command->i], command->j - command->var_name_len);
		ft_strlcpy(command->new_command + command->j - command->var_name_len - 1, \
		command->var_value, ft_strlen(command->var_value) + 1);
		free_malloced(command->commands, command->is_malloced ,command->i);
		command->commands[command->i] = command->new_command;
		command->is_malloced[command->i] = 1;
	}
	return ;
}

void	handle_commands(t_command_data *command)
{
	command->j = 0;
	while (command->commands[command->i][command->j] != '\0')
	{
		if (command->commands[command->i][command->j] == '$'
			&& command->commands[command->i][command->j + 1] != '?'
			&& (is_single_quote(command->commands[command->i], \
			command->j) == 0))
			handle_variable_expansion(command);
		else
			command->j++;
	}
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

void	parse_command(t_shell *shell)
{
	add__history(shell->history, shell->input);
	if (handle_exception(shell->input) == 0)
		return ;
	shell->command->commands[shell->command->i] = ft_strtok(shell->input, "|");
	while (shell->command->commands[shell->command->i] != NULL)
	{
		handle_commands(shell->command);
		shell->command->i++;
		shell->command->commands[shell->command->i] = ft_strtok(NULL, "|");
	}
	chose_command(shell);
}
