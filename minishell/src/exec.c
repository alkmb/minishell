/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/02/16 13:41:45 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

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
			waitpid(pid, &g_exit_status, 0);
			if (WIFEXITED(g_exit_status))
				g_exit_status = WEXITSTATUS(g_exit_status);
		}
		else
			execute_child_process(cmd_path, args);
	}
	else
		g_exit_status = 127;
	free(cmd_path);
	printf("status: %d\n", g_exit_status);
	return (g_exit_status);
}

void	execute_builtin_command(char **args)
{
	if (args[0] != NULL)
	{
		chose_built_in(args);
	}
	if (g_exit_status != 0)
	{
		g_exit_status = execute_external_command(args);
		if (g_exit_status != 0)
			ft_printf("minishell: %s: command not found\n", args[0]);
	}
}

int	chose_built_in(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		g_exit_status = cmd_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		g_exit_status = cmd_pwd();
	else if (ft_strcmp(args[0], "unset") == 0)
		g_exit_status = cmd_unset(args);
	else if (ft_strcmp(args[0], "export") == 0)
		g_exit_status = cmd_export(args);
	else
	{
		g_exit_status = 127;
		return (127);
	}
	return (0);
}
