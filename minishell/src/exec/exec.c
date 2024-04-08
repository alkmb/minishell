/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/04/08 09:52:20 by akambou          ###   ########.fr       */
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

int	execute_external_command(char **args)
{
	char	*cmd_path;
	pid_t	pid;
	int		exit_status;

	exit_status = 0;
	cmd_path = find_command(args[0]);
	if (cmd_path != NULL)
	{
		pid = fork();
		if (pid == -1)
			return (free(cmd_path), 0);
		else if (pid > 0)
		{
			waitpid(pid, &exit_status, 0);
			if (WIFEXITED(exit_status))
				exit_status = WEXITSTATUS(exit_status);
		}
		else
			execute_child_process(cmd_path, args);
	}
	else
	{
		exit_status = 127;
		ft_printf("minishell: %s: command not found\n", args[0]);
	}
	return (free(cmd_path), exit_status);
}
