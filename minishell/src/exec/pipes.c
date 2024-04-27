/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:13:04 by akambou           #+#    #+#             */
/*   Updated: 2024/04/27 02:00:16 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_child(t_shell *shell)
{
	shell->data->args = token_pipe_cmd(shell);
	builtin_cmds(shell);
	pipe(shell->data->fd);
	shell->data->pid = fork();
	if (shell->data->pid == 0)
	{
		if (shell->data->fd_in != 0)
		{
			dup2(shell->data->fd_in, STDIN_FILENO);
			close(shell->data->fd_in);
		}
		if (shell->data->i != shell->command->i)
			dup2(shell->data->fd[1], STDOUT_FILENO);
		execute_pipe(shell);
		exit(shell->data->status);
	}
	else
	{
		waitpid(shell->data->pid, &shell->data->status, 0);
		if (WIFEXITED(shell->data->status))
			shell->status = WEXITSTATUS(shell->data->status);
	}
}

void	handle_parent(t_pipe_data *data)
{
	if (data->pid > 0)
	{
		wait(NULL);
		if (data->fd_in != 0)
			close(data->fd_in);
		data->fd_in = data->fd[0];
		close(data->fd[1]);
		data->i++;
		free_args(data->args);
	}
}

void	chose_pipe(t_shell *shell)
{
	while (shell->data->i <= shell->command->i)
	{
		handle_child(shell);
		handle_parent(shell->data);
	}
}

void	execute_pipe(t_shell *shell)
{
	int	orig_stdin;
	int	orig_stdout;

	handle_redirection(shell->data->args, &orig_stdin, &orig_stdout);
	close(shell->data->fd[0]);
	close(shell->data->fd[1]);
	if (ft_strcmp(shell->data->args[0], "env") != 0
		&& ft_strcmp(shell->data->args[0], "cd") != 0 && \
		ft_strcmp(shell->data->args[0], "echo") != 0
		&& ft_strcmp(shell->data->args[0], "pwd") != 0 && \
		ft_strcmp(shell->data->args[0], "export") != 0
		&& ft_strcmp(shell->data->args[0], "unset") \
		!= 0 && ft_strcmp(shell->data->args[0], "exit") != 0
		&& ft_strcmp(shell->data->args[0], "history") != 0)
		execute_external_command(shell);
	if (ft_strcmp(shell->data->args[0], "env") == 0)
		handle_env(shell->environ);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}
