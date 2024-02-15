/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/02/15 05:46:22 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_command_in_path(char *command, char *path_copy, int max_length)
{
	char	*dir;
	char	*cmd_path;

	dir = ft_strtok(path_copy, ":");
	while (dir != NULL)
	{
		cmd_path = malloc(max_length);
		if (cmd_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		ft_strlcpy(cmd_path, dir, max_length);
		ft_strlcat(cmd_path, "/", max_length);
		ft_strlcat(cmd_path, command, max_length);
		if (access(cmd_path, X_OK) == 0)
		{
			free(path_copy);
			return (cmd_path);
		}
		free(cmd_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	return (NULL);
}

char	*find_command(char *command)
{
	char	*path;
	char	*path_copy;
	int		max_length;

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	max_length = ft_strlen(path) + 2 * ft_strlen(command) + 2;
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
		{
			free(path_copy);
			return (ft_strdup(command));
		}
	}
	return (find_command_in_path(command, path_copy, max_length));
}

int	execute_external_command(char **args)
{
	int		status;
	char	*cmd_path;
	pid_t	pid;

	cmd_path = find_command(args[0]);
	if (cmd_path != NULL)
	{
		pid = fork();
		if (pid == -1)
			return (free(cmd_path), 0);
		else if (pid > 0)
		{
			waitpid(pid, &status, 0);
			return (free(cmd_path), WEXITSTATUS(status));
		}
		else
			execute_child_process(cmd_path, args);
	}
	else
	{
		free(cmd_path);
		return (status);
	}
	return (status);
}

void	execute_builtin_command(char **args, int exit_status)
{
	if (args[0] != NULL)
	{
		chose_built_in(args, &exit_status);
	}
	if (exit_status != 0)
	{
		exit_status = execute_external_command(args);
		if (exit_status != 0)
			ft_printf("minishell: %s: command not found\n", args[0]);
		exit_status = 0;
	}
}

void	execute_builtin_commandenv(char **args, char **environ)
{
	int	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[0], "env") == 0)
		{
			cmd_env(environ);
			return ;
		}
		i++;
	}
}
