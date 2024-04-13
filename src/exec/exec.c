/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/04/13 01:59:03 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_bin(t_shell *shell)
{
	if (execve(shell->data->cmd_path, shell->data->args, shell->environ) == -1)
	{
		free(shell->data->cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	execute_external_command(t_shell *shell)
{
	pid_t	pid;

	shell->data->cmd_path = find_command(shell->data->args[0]);
	if (shell->data->cmd_path != NULL)
	{
		signal(SIGINT, SIG_IGN);
		pid = fork();
		if (pid == -1)
			return (free(shell->data->cmd_path));
		else if (pid > 0)
		{
			waitpid(pid, &shell->data->status, 0);
			if (WIFEXITED(shell->data->status))
				shell->data->status = WEXITSTATUS(shell->data->status);
		}
		else
			execute_bin(shell);
	}
	else if (shell->data->cmd_path == NULL)
	{
		shell->data->status = 127;
		ft_printf("minishell: %s: command not found\n", shell->data->args[0]);
	}
	free(shell->data->cmd_path);
}
