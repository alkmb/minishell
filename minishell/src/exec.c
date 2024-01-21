/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/01/21 05:08:21 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *find_command(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	int max_length = strlen(path) + 2 * strlen(command) + 2;
	char *cmd_path = malloc(max_length);

	while (dir != NULL)
	{
		strlcpy(cmd_path, dir, strlen(dir) + 1);
		strcat(cmd_path, "/");
		strlcat(cmd_path, command, max_length);
		if (access(cmd_path, X_OK) == 0)
		{
			free(path_copy);
			return cmd_path;
		}
		dir = strtok(NULL, ":");
	}

	free(path_copy);
	free(cmd_path);
	return NULL;
}

int execute_external_command(char **args)
{
	char *cmd_path = find_command(args[0]);
	if (cmd_path != NULL)
	{
		pid_t pid = fork();
		if (pid == -1)
			return 0;
		else if (pid > 0)
		{
			int status;
			waitpid(pid, &status, 0);
		}
		else
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				return 0;
				perror("minishell");
			}
			exit(EXIT_FAILURE);
		}
		free(cmd_path);
	}
	return 1;
}

void execute_builtin_command(char **args)
{
	int i = 0;

	while (commands[i].name != NULL)
	{
		if (ft_strcmp(args[0], commands[i].name) == 0)
		{
			commands[i].func(args);
			return;
		}
		i++;
	}
	if (execute_external_command(args) == 0)
	{
		ft_printf("minishell: command not found: %s\n", args[0]);
	}
}

void execute_builtin_commandenv(char **args, char **environ)
{
	int i = 0;

	while (commandsenv[i].name != NULL)
	{
		if (args[0] != NULL && ft_strcmp(args[0], commandsenv[i].name) == 0)
		{
			commandsenv[i].func(environ);
			return;
		}
		else if (ft_strcmp(args[0], "exit") == 0)
			exit(0);
		i++;
	}
}

void cmd_env(char **environ)
{
	char *env_var = *environ;
	while (env_var != NULL)
	{
		ft_printf("%s\n", env_var);
		env_var = *(environ++);
	}
}
