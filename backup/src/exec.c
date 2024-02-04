/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/01/22 03:14:05 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_command(char *command)
{
	char	*path;
	char	*path_copy;
	char	*dir;
	char	*cmd_path;
	int		max_length;

	path = getenv("PATH");
	path_copy = ft_strdup(path);
	dir = ft_strtok(path_copy, ":");
	max_length = ft_strlen(path) + 2 * ft_strlen(command) + 2;
	cmd_path = malloc(max_length);
	while (dir != NULL)
	{
		ft_strlcpy(cmd_path, dir, strlen(dir) + 1);
		ft_strlcat(cmd_path, "/", max_length);
		ft_strlcat(cmd_path, command, max_length);
		if (access(cmd_path, X_OK) == 0)
			return (free(path_copy), cmd_path);
		dir = ft_strtok(NULL, ":");
	}
	free(path_copy);
	free(cmd_path);
	return (NULL);
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
		{
			if (execve(cmd_path, args, environ) == -1)
			{
				free(cmd_path);
				exit(EXIT_FAILURE);
			}
		}
	}
	return (127);
}

void	execute_builtin_command(char **args, int *exit_status)
{
	if (args[0] != NULL)
	{
		*exit_status = chose_built_in(args, exit_status);
	}
	if (*exit_status != 0)
		*exit_status = execute_external_command(args);
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
		else if (ft_strcmp(args[0], "exit") == 0)
		{
			ft_printf("exit\n");
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

void	cmd_env(char **environ)
{
	char	*env_var;

	env_var = *environ;
	while (env_var != NULL)
	{
		ft_printf("%s\n", env_var);
		env_var = *(environ++);
	}
}
