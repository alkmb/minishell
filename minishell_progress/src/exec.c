/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 09:56:10 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*--------------------------all comands executionm-----------------------------*/
void execute_builtin_command(char **args)
{
	int i = 0;

	if (ft_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
			fprintf(stderr, "cd: expected argument\n");
		else
		{
			if (chdir(args[1]) != 0)
				perror("cd");
		}
	}
	else
	{
		while ( commands[i].name != NULL)
		{
			if (ft_strcmp(args[0], commands[i].name) == 0)
			{
				commands[i].func(args);
				return;
			}
			i++;
		}
	}
}
/*--------------------------------------------------------------------------------*/

/*--------------------------only for env executionm-----------------------------*/
void execute_builtin_commandenv(char **args, char **environ)
{
	int i = 0;

	while ( commandsenv[i].name != NULL)
	{
		if (ft_strcmp(args[0], commandsenv[i].name) == 0)
		{
			commandsenv[i].func(environ);
			return;
		}
		i++;
	}
}
/*--------------------------------------------------------------------------------*/

void execute_command(char *commands[], int n)
{
	if (n < 0)
		return;
	if (n == 0)
	{
		char *args[MAX_ARGS];
		int i = 0;
		args[i] = strtok(commands[n], " ");
		while (args[i] != NULL) {
			i++;
			args[i] = strtok(NULL, " ");
		}
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		return;
	}
	int fd[2];
	pid_t pid;
	if (pipe(fd) == -1) {
		perror("Error creating pipe");
		exit(EXIT_FAILURE);
	}
	if ((pid = fork()) == -1) {
		perror("Error forking process");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		close(fd[0]);
		if (n > 0)
			dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char *args[MAX_ARGS];
		int i = 0;
		args[i] = strtok(commands[n], " ");
		while (args[i] != NULL)
		{
			i++;
			args[i] = strtok(NULL, " ");
		}
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		exit(EXIT_FAILURE);
	}
	else
	{
		close(fd[1]);
		if (n > 0) {

			dup2(fd[0], STDIN_FILENO);
		}
		close(fd[0]);
		wait(NULL);
		execute_command(commands, n - 1);
	}
}
