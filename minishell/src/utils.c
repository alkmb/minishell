/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:57:37 by kmb               #+#    #+#             */
/*   Updated: 2024/02/01 10:40:00 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	ft_printf("%s@minimalianteo$ ", getenv("USER"));
	if (sig == SIGINT)
	{
		ft_printf("\n");
		rl_on_new_line();
		//rl_replace_line("", 0);
		rl_redisplay();
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
	else
		return (127);
	return (0);
}
