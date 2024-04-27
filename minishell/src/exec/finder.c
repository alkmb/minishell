/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 22:25:01 by kmb               #+#    #+#             */
/*   Updated: 2024/04/10 00:58:36 by akambou          ###   ########.fr       */
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
	if (path == NULL)
		return (NULL);
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
