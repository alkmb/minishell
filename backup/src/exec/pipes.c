/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:13:04 by akambou           #+#    #+#             */
/*   Updated: 2024/03/19 06:26:16 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	int	exit_status;

	handle_redirection(args, &orig_stdin, &orig_stdout);
	close(fd[0]);
	close(fd[1]);
	if (ft_strcmp(args[0], "env") != 0 && ft_strcmp(args[0], "cd") != 0 && \
		ft_strcmp(args[0], "echo") != 0 && ft_strcmp(args[0], "pwd") != 0 && \
		ft_strcmp(args[0], "export") != 0 && ft_strcmp(args[0], "unset") \
		!= 0 && ft_strcmp(args[0], "exit") != 0)
		exit_status = execute_external_command(args);
	if (ft_strcmp(args[0], "env") == 0)
		handle_env(environ);
	printf("status: %d\n", exit_status);
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
	exit(EXIT_SUCCESS);
}
