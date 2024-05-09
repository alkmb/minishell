/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/05/09 19:00:47 by akambou          ###   ########.fr       */
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
}

void	execute_bin(t_shell *shell)
{
	if (execve(shell->data->cmd_path, shell->data->args, \
	shell->environ) == -1)
	{
		printf("minishell: %s: %s\n", shell->data->args[0], strerror(errno));
		free(shell->data->cmd_path);
		exit(EXIT_FAILURE);
	}
}

void	print_command_not_found(t_shell *shell)
{
	shell->data->status = 127;
	write (2, "minishell: ", 11);
	write(2, shell->data->args[0], ft_strlen(shell->data->args[0]));
	write(2, ": command not found\n", 20);
}

void	execute_external_command(t_shell *shell)
{
	pid_t	pid;

	shell->data->cmd_path = find_command(shell, shell->data->args[0]);
	if (shell->data->cmd_path != NULL)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
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
		print_command_not_found(shell);
	free(shell->data->cmd_path);
}
