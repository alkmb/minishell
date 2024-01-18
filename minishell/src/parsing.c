/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/01/18 08:06:15 by kmb              ###   ########.fr       */
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
	if (n == 0 && commands[1] != NULL)
	{
		char **args;
		args = token_single_cmd(commands, 0);
		execute_builtin_commandenv(args, environ);
		execute_builtin_command(args);
		return;
	}
	else
		chose_pipe(commands, n);
}
void	execute_pipe(int fd[2], char **args)
{
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
		char **args = token_pipe_cmd(commands, i);

		if (strcmp(args[0], "cd") == 0)
			cmd_cd(args);
		else
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
				execute_pipe(fd, args);
			}
			else
			{
				wait(NULL);
				if (fd_in != 0)
					close(fd_in);
				fd_in = fd[0];
				close(fd[1]);
			}
		}
		free(args);
		i++;
	}
}
