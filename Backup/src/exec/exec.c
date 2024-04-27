/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/04/16 02:22:40 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_env(char **environ)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		ft_printf("%s\n", environ[i]);
		i++;
	}
}

void	builtin_cmds(t_shell *shell)
{
	if (ft_strcmp(shell->data->args[0], "cd") == 0)
		cmd_cd(shell);
	if (ft_strcmp(shell->data->args[0], "echo") == 0)
		cmd_echo(shell);
	else if (ft_strcmp(shell->data->args[0], "pwd") == 0)
		cmd_pwd();
	else if (ft_strcmp(shell->data->args[0], "export") == 0)
		cmd_export(shell);
	else if (ft_strcmp(shell->data->args[0], "unset") == 0)
		cmd_unset(shell);
	else if (ft_strcmp(shell->data->args[0], "history") == 0)
		ft_printf("%s", cmd_history(shell->history));
	else if (ft_strcmp(shell->data->args[0], "status") == 0)
		ft_printf("status: %d\n", shell->status);
	else if (ft_strcmp(shell->data->args[0], "exit") == 0)
	{
		ft_printf("exit\n");
		exit(EXIT_SUCCESS);
	}
}

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