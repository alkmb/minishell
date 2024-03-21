/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:13:04 by akambou           #+#    #+#             */
/*   Updated: 2024/03/21 02:52:49 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_child(t_pipe_data *data, char *commands[], int n)
{
	data->args = token_pipe_cmd(commands, data->i);
	handle_builtin_commands(data->args);
	pipe(data->fd);
	data->pid = fork();
	if (data->pid == 0)
	{
		handle_child_process(data->fd_in);
		if (data->i != n)
			dup2(data->fd[1], STDOUT_FILENO);
		data->status = execute_pipe(data->fd, data->args, data->status);
		printf("status: %d\n", data->status);
		if (ft_strcmp(data->args[0], "$?") == 0)
		{
			ft_printf("status: %d\n", data->status);
		}
		exit(data->status);
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

void	chose_pipe(char *commands[], int n)
{
	t_pipe_data	data;

	initialize_variables(&data.i, &data.fd_in);
	while (data.i <= n)
	{
		handle_child(&data, commands, n);
		handle_parent(&data);
	}
}

int	execute_pipe(int fd[2], char **args, int exit_status)
{
	int	orig_stdin;
	int	orig_stdout;

	if (ft_strcmp(args[0], "cat") == 0)
		signal(SIGINT, handle_sigquit);
	handle_redirection(args, &orig_stdin, &orig_stdout);
	close(fd[0]);
	close(fd[1]);
	if (ft_strcmp(args[0], "env") != 0 && ft_strcmp(args[0], "cd") != 0 && \
		ft_strcmp(args[0], "echo") != 0 && ft_strcmp(args[0], "pwd") != 0 && \
		ft_strcmp(args[0], "export") != 0 && ft_strcmp(args[0], "unset") \
		!= 0 && ft_strcmp(args[0], "exit") != 0 && ft_strcmp(args[0], "$?") \
		!= 0)
		exit_status = execute_external_command(args);
	if (ft_strcmp(args[0], "env") == 0)
		handle_env(environ);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	return (exit_status);
}
