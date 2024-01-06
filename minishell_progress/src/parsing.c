/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 16:58:08 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void parse_command(char *input)
{
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

void handle_pipes(char *commands[], int n)
{
	char *args[MAX_ARGS];
	int fd[2];
	pid_t pid1, pid2;

	int i = 0;
	char *saveptr;
	args[i] = ft_strtok_r(commands[n], " ", &saveptr);
	while (args[i] != NULL)
	{
		i++;
		args[i] = ft_strtok(NULL, " ");
	}
	if (pipe(fd) == -1) {
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
	pid1 = fork();
	if (pid1 == -1) {
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0) {
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		exit(EXIT_SUCCESS);
	}
	pid2 = fork();
	if (pid2 == -1) {
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0) {
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		exit(EXIT_SUCCESS);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}
