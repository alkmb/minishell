/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:49:13 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 00:43:09 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_parent_process(int *fd_in, int *fd)
{
	// wait(NULL) waits for the child process to finish
	wait(NULL);
	// if the input file descriptor is not 0, close it
	if (*fd_in != 0)
		close(*fd_in);
	// set the input file descriptor to the output file descriptor
	*fd_in = fd[0];
	close(fd[1]);
}

void	handle_child_process(int fd_in)
{
	// if the input file descriptor is not 0, duplicate it to the standard input file descriptor
	if (fd_in != 0)
	{
		// duplicate the input file descriptor to the standard input file descriptor
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
