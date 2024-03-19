/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:49:13 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 06:23:08 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_parent_process(int *fd_in, int *fd)
{
	wait(NULL);
	if (*fd_in != 0)
		close(*fd_in);
	*fd_in = fd[0];
	close(fd[1]);
}

void	handle_child_process(int fd_in)
{
	if (fd_in != 0)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
}

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

void	handle_builtin_commands(char **args)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cmd_cd(args);
	if (ft_strcmp(args[0], "echo") == 0)
		cmd_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		cmd_pwd();
	else if (ft_strcmp(args[0], "export") == 0)
		cmd_export(args);
	else if (ft_strcmp(args[0], "unset") == 0)
		cmd_unset(args);
	else if (ft_strcmp(args[0], "exit") == 0)
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
