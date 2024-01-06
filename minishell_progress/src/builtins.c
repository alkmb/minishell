/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/01/06 11:20:53 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_echo(char **args)
{
	int i = 1;
	int n_flag = 0;

	if (args[1] != NULL && strcmp(args[1], "-n") == 0)
	{
		n_flag = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (n_flag == 0)
		ft_printf("\n");
}

void cmd_pwd()
{
	char cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_printf("%s\n", cwd);
	}
	else
	{
		perror("getcwd() error");
	}
}

void cmd_unset(char **args)
{
	if (args[1] != NULL)
		unsetenv(args[1]);
	else
		fprintf(stderr, "Usage: unset variable_name\n");
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
		fprintf(stderr, "Usage: export variable_name value\n");
}
