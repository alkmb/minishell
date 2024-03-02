/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/03/02 23:06:44 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status = 0;

void	execute_child_process(char *cmd_path, char **args)
{
	if (execve(cmd_path, args, environ) == -1)
	{
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
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
		i++;
	}
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
		if (ft_strcmp(args[0], "echo") == 0)
			g_exit_status = cmd_echo(args);
		else if (ft_strcmp(args[0], "pwd") == 0)
			g_exit_status = cmd_pwd();
		else if (ft_strcmp(args[0], "export") == 0)
			g_exit_status = cmd_export(args);
		else
			g_exit_status = 127;
	}
	if (g_exit_status != 0)
	{
		g_exit_status = execute_external_command(args);
		if (g_exit_status != 0)
			ft_printf("minishell: %s: command not found\n", args[0]);
	}
}
