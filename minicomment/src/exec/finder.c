/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 22:25:01 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 00:48:10 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_command_in_path(char *command, char *path_copy, int max_length)
{
	char	*dir;
	char	*cmd_path;

	// split the path into directories
	dir = ft_strtok(path_copy, ":");
	// loop through the directories
	while (dir != NULL)
	{
		// create the path to the command
		cmd_path = malloc(max_length);
		if (cmd_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}
		// check if the command is executable
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
	// check if the command is executable
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, X_OK) == 0)
		{
			free(path_copy);
			return (ft_strdup(command));
		}
	}
	// check if the command is in the path
	return (find_command_in_path(command, path_copy, max_length));
}
