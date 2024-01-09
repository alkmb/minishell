/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:22 by kmb               #+#    #+#             */
/*   Updated: 2024/01/09 13:56:37 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute_builtin_command(char **args)
{
	int i = 0;

	while (commands[i].name != NULL)
	{
		if (ft_strcmp(args[0], commands[i].name) == 0)
		{
			commands[i].func(args);
			return;
		}
		i++;
	}
	if (execvp(args[0], args) == -1)
		perror("minishell");
	exit(EXIT_FAILURE);
}

void execute_builtin_commandenv(char **args, char **environ)
{
	int i = 0;

	while (commandsenv[i].name != NULL)
	{
		if (args[0] != NULL && ft_strcmp(args[0], commandsenv[i].name) == 0)
		{
			commandsenv[i].func(environ);
			return;
		}
		i++;
	}
}

void cmd_env(char **environ)
{
	char *env_var = *environ;
	while (env_var != NULL)
	{
		ft_printf("%s\n", env_var);
		env_var = *(environ++);
	}
}

void handle_sigint(int sig)
{
	ft_printf("%s@minimalianteo$ ", getenv("USER"));
	ft_printf("%d\n", sig);
}
