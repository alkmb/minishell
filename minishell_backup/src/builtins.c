/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/01/04 22:44:55 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_echo(char **args)
{
	int i = 1;

	if (args[i] != NULL && ft_strncmp(args[i], "-n", 2) == 0)
		i++;
	else
	{
		ft_printf("Usage: echo -n [string...]\n");
		return;
	}

	while (args[i] != NULL)
	{
		ft_printf("%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
}

void cmd_pwd(void)
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

void cmd_cd(char **args)
{
	if (args[1] == NULL || args[2] != NULL)
	{
		ft_printf("Usage: cd directory\n");
		return;
	}

	if (chdir(args[1]) != 0)
	{
		perror(args[1]);
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

void cmd_export(char **args)
{
	if (args[1] != NULL && args[2] != NULL)
		setenv(args[1], args[2], 1);
	else
		fprintf(stderr, "Usage: export variable_name value\n");
}

void execute_command(char **args, char **environ)
{
	if (ft_strncmp(args[0], "unset", 5) == 0)
		cmd_unset(args);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		cmd_cd(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		cmd_env(environ);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		cmd_export(args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	else if (ft_strncmp(args[0], "echo", 4) == 0)
		cmd_echo(args);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		cmd_pwd();
	else
		return;
}
