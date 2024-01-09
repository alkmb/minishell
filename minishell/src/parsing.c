/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/01/09 13:57:43 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void parse_command(char *input, CommandHistory* history)
{
	add_to_history(history, input);

	int i = 0;
	char *commands[7];

	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		i++;
		commands[i] = ft_strtok(NULL, "|");
	}
	chose_command(commands, i - 1);
}

void chose_command(char *commands[], int n)
{
	if (n < 0)
		return;
	if (n == 0)
	{
		char *args[MAX_ARGS];
		int i = 0;
		args[i] = ft_strtok(commands[n], " ");
		while (args[i] != NULL) {
			i++;
			args[i] = ft_strtok(NULL, " ");
		}
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		return;
	}
	else
		handle_pipes(commands, n);
}

void single_command(char *args[], int fd[])
{
	dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	close(fd[1]);
	execute_builtin_commandenv(args, environ);
	execute_builtin_command(args);
	exit(EXIT_SUCCESS);
}

void chose_pipe(char *commands[], int n)
{
	int i = 0;
	pid_t pid;
	int fd[2];
	int fd_in = 0;

	while(i <= n)
	{
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (fd_in != 0)
			{
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (i != n)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			char *args[MAX_ARGS];
			int j = 0;
			char *saveptr;
			args[j] = ft_strtok_r(commands[i], " ", &saveptr);
			while (args[j] != NULL)
				args[++j] = ft_strtok(NULL, " ");
			execute_builtin_commandenv(args, environ);
			execute_builtin_command(args);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			if (fd_in != 0)
				close(fd_in);
			fd_in = fd[0];
			close(fd[1]);
		}
		i++;
	}
}

void handle_pipes(char *commands[], int n)
{
	char *args[MAX_ARGS];
	int fd[2];
	pid_t pid;
	int i = 0;
	char *saveptr;

	args[i] = ft_strtok_r(commands[n], " ", &saveptr);
	while (args[i] != NULL)
		args[++i] = ft_strtok(NULL, " ");
	if (pipe(fd) == -1)
		perror("Error creating pipe");
	pid = fork();
	if (pid == 0 && args[0] == NULL)
		single_command(args, fd);
	else
		chose_pipe(commands, n);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
}
