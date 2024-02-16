/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:13:04 by akambou           #+#    #+#             */
/*   Updated: 2024/02/16 12:37:06 by akambou          ###   ########.fr       */
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

void	chose_pipe(char *commands[], int n)
{
	int		i;
	int		fd_in;
	pid_t	pid;
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
			execute_pipe(fd, args);
		}
		else
			handle_parent_process(&fd_in, fd);
		i++;
		free_args(args);
	}
}

void	execute_pipe(int fd[2], char **args)
{
	int	orig_stdin;
	int	orig_stdout;

	handle_redirection(args, &orig_stdin, &orig_stdout);
	close(fd[0]);
	close(fd[1]);
	execute_builtin_commandenv(args, environ);
	execute_builtin_command(args);
	restore_io(STDIN_FILENO, STDOUT_FILENO);
	exit(EXIT_SUCCESS);
}
