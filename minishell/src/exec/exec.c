/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/04/09 02:21:03 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_child_process(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
}

int	execute_external_command(char **args, t_pipe_data *data)
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
			waitpid(pid, &data->status, 0);
			if (WIFEXITED(data->status))
				data->status = WEXITSTATUS(data->status);
		}
		else
			execute_child_process(cmd_path, args);
	}
	else if (cmd_path == NULL)
	{
		data->status = 127;
		ft_printf("minishell: %s: command not found\n", args[0]);
	}
	return (free(cmd_path), data->status);
}
