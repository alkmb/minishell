/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2023/12/20 23:35:50 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void cmd_unset(char **args)
{
	if (args[1] != NULL)
		unsetenv(args[1]);
	else
		fprintf(stderr, "Usage: unset variable_name\n");
}

void cmd_cd(char **args)
{
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
			perror("chdir failed");
		else
			fprintf(stderr, "Usage: cd directory_path\n");
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

void cmd_external(char **args)
{
	pid_t pid = fork();
	if (pid == 0)
	{
		execvp(args[0], args);
		perror("Command not found");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("Fork failed");
	else
		wait(NULL);
}

void execute_command(char **args, char **env)
{
	if (ft_strncmp(args[0], "unset", 5) == 0)
		cmd_unset(args);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		cmd_cd(args);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		cmd_env(env);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		cmd_export(args);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit(EXIT_SUCCESS);
	else
		cmd_external(args);
}
