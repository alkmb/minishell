/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 13:41:02 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_pwd(void)
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
		perror("getcwd() error");
}

void cmd_unset(char **args)
{
	if (args[1] != NULL)
		unsetenv(args[1]);
	else
		ft_printf("Usage: unset variable_name\n");
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

void cmd_export(char **args)
{
	if (args[1] != NULL && args[2] != NULL)
		setenv(args[1], args[2], 1);
	else
		ft_printf("Usage: export variable_name value\n");
}

void handle_sigint(int sig)
{
	ft_printf("%s@minimalianteo$ ", getenv("USER"));
	ft_printf("%d\n", sig);
}
