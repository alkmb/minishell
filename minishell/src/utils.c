/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:57:37 by kmb               #+#    #+#             */
/*   Updated: 2024/02/05 02:09:13 by akambou          ###   ########.fr       */
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

int	is_single_quote(char *str, int index)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (i < index)
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (0);
	else
		return (1);
}

void	restore_io(int orig_stdin, int orig_stdout)
{
	dup2(orig_stdin, STDIN_FILENO);
	dup2(orig_stdout, STDOUT_FILENO);
	close(orig_stdin);
	close(orig_stdout);
}

void	free_malloced(char *commands[], int is_malloced[], int i)
{
	int	j;

	j = 0;
	while (j <= i)
	{
		if (is_malloced[j])
			free(commands[j]);
		j++;
	}
}

int	chose_built_in(char **args, int *exit_status)
{
	if (ft_strcmp(args[0], "echo") == 0)
		*exit_status = cmd_echo(args);
	else if (ft_strcmp(args[0], "pwd") == 0)
		*exit_status = cmd_pwd();
	else if (ft_strcmp(args[0], "unset") == 0)
		*exit_status = cmd_unset(args);
	else if (ft_strcmp(args[0], "export") == 0)
		*exit_status = cmd_export(args);
	else if (ft_strcmp(args[0], "$?") == 0)
		printf("%d\n", *exit_status);
	else if (ft_strcmp(args[0], "cd") == 0)
		*exit_status = 0;
	else
	{
		*exit_status = 127;
		return (127);
	}
	return (0);
}