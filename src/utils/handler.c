/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:49:13 by kmb               #+#    #+#             */
/*   Updated: 2024/04/13 01:48:23 by kmb              ###   ########.fr       */
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

int	handle_exception(char *input)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(input);
	if (ft_strcmp(input, EXCEPTION) == 0)
	{
		printf(EXCEPTION_R);
		return (0);
	}
	else if (ft_strncmp(input, " ", 1) == 0)
	{
		while (input[i] == ' ')
			i++;
		if (i == len)
		{
			return (0);
		}
	}
	return (1);
}
