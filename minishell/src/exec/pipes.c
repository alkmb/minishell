/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:13:04 by akambou           #+#    #+#             */
/*   Updated: 2024/03/04 15:11:45 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_parent_process(int *fd_in, int *fd)
{
	wait(NULL);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = fd[0];
	close(fd[1]);
}

void	handle_child_process(int fd_in)
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

void	handle_builtin_commands(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cmd_cd(args);
	else if (ft_strcmp(args[0], "export") == 0)
		cmd_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		cmd_unset(args);
	else if (ft_strcmp(args[0], "env") == 0)
		cmd_env(environ);
	else if (ft_strcmp(args[0], "exit") == 0)
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

int	chose_pipe(char *commands[], int n)
{
	int		i;
	int		fd_in;
	pid_t	pid;
	int		status;
	int		fd[2];
	char	**args;

	initialize_variables(&i, &fd_in);
	while (i <= n)
	{
		args = token_pipe_cmd(commands, i);
		handle_builtin_commands(args);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			handle_child_process(fd_in);
			if (i != n)
				dup2(fd[1], STDOUT_FILENO);
			status = execute_pipe(fd, args);
		}
		else
			handle_parent_process(&fd_in, fd);
		i++;
		free_args(args);
	}
	return status;
}

int	execute_pipe(int fd[2], char **args)
{
	int	orig_stdin;
	int	orig_stdout;
	int	status;

	handle_redirection(args, &orig_stdin, &orig_stdout);
	close(fd[0]);
	close(fd[1]);
	execute_builtin_commandenv(args, environ);
	status = execute_builtin_command(args);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	return (status);
	close(orig_stdin);
	close(orig_stdout);
	exit(EXIT_SUCCESS);
}
