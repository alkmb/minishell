/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:13:04 by akambou           #+#    #+#             */
/*   Updated: 2024/04/09 02:31:52 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_child(t_pipe_data *data, t_command_data *command, \
t_commandhistory *history)
{
	data->args = token_pipe_cmd(command, data);
	handle_builtin_commands(data->args, history);
	pipe(data->fd);
	data->pid = fork();
	if (data->pid == 0)
	{
		handle_child_process(data->fd_in);
		if (data->i != command->i)
			dup2(data->fd[1], STDOUT_FILENO);
		execute_pipe(data->fd, data->args, data);
		exit(data->status);
	}
	else
	{
		waitpid(data->pid, &data->status, 0);
		if (WIFEXITED(data->status))
			data->status = WEXITSTATUS(data->status);
	}
	return (data->status);
}

void	handle_parent(t_pipe_data *data)
{
	if (data->pid > 0)
	{
		handle_parent_process(&data->fd_in, data->fd);
		data->i++;
		free_args(data->args);
	}
}

int	chose_pipe(t_command_data *command, t_pipe_data *data, \
t_commandhistory *history)
{
	while (data->i <= command->i)
	{
		data->status = handle_child(data, command, history);
		handle_parent(data);
	}
	return (data->status);
}

int	execute_pipe(int fd[2], char **args, t_pipe_data *data)
{
	int	orig_stdin;
	int	orig_stdout;

	handle_redirection(args, &orig_stdin, &orig_stdout);
	close(fd[0]);
	close(fd[1]);
	if (ft_strcmp(args[0], "env") != 0 && ft_strcmp(args[0], "cd") != 0 && \
		ft_strcmp(args[0], "echo") != 0 && ft_strcmp(args[0], "pwd") != 0 && \
		ft_strcmp(args[0], "export") != 0 && ft_strcmp(args[0], "unset") \
		!= 0 && ft_strcmp(args[0], "exit") != 0 && \
		ft_strcmp(args[0], "history") != 0 && ft_strcmp(args[0], "$?") != 0)
		execute_external_command(args, data);
	if (ft_strcmp(args[0], "env") == 0)
		handle_env(environ);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	return (data->status);
}
