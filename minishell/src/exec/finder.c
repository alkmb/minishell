/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 22:25:01 by kmb               #+#    #+#             */
/*   Updated: 2024/05/05 17:39:00 by kmb              ###   ########.fr       */
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

char	*get_env_value(char *key, char **environ)
{
	int	i;
	int	key_len;

	key_len = ft_strlen(key);
	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], key, key_len) == 0
			&& environ[i][key_len] == '=')
			return (&environ[i][key_len + 1]);
		i++;
	}
	return (NULL);
}

char	*find_command(t_shell *shell, char *command)
{
	char	*path;
	char	*path_copy;
	int		max_length;

	path = get_env_value("PATH", shell->environ);
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
