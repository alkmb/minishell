/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/02/05 00:08:00 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cmd_echo(char **args)
{
	int	i;
	int	newline;

	newline = 0;
	i = 1;
	if (args[i] != NULL && ft_strcmp(args[i], "-n") == 0)
	{
		newline = 1;
		i++;
	}
	while (args[i] != NULL)
	{
		fprintf(stderr, "%s", args[i]);
		if (args[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (newline)
		ft_printf("\n");
	return (0);
}

int	cmd_cd(char **args)
{
	char *path;

	if (args[1] != NULL)
	{
		if (args[1][0] == '~')
		{
			path = malloc(strlen(getenv("HOME")) + strlen(args[1]));
			strcpy(path, getenv("HOME"));
			strcat(path, args[1] + 1); // +1 to skip the '~'
		}
		else
		{
			path = args[1];
		}

		if (chdir(path) != 0)
		{
			perror(path);
			if (args[1][0] == '~')
				free(path); // Free the allocated memory if we allocated any
			return (127);
		}

		if (args[1][0] == '~')
			free(path); // Free the allocated memory if we allocated any
	}
	else
		chdir(getenv("HOME"));
	return (0);
}

int	cmd_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("getcwd() error");
		return (127);
	}
	return (0);
}

int	cmd_unset(char **args)
{
	int	i;
	int	j;
	char *name;
	char *env_var;

	if (args[1] != NULL)
	{
		i = 0;
		while (environ[i])
		{
			env_var = strdup(environ[i]);
			name = strtok(env_var, "=");
			if (ft_strcmp(name, args[1]) == 0)
			{
				for (j = i; environ[j]; j++)
					environ[j] = environ[j + 1];
				free(env_var);
				break ;
			}
			free(env_var);
			i++;
		}
	}
	else
	{
		fprintf(stderr, "unset: not enough arguments\n");
		return (127);
	}
	return (0);
}

int	cmd_export(char **args)
{
	char	**env;
	char	*name;
	char    *value;
	int	i;

	env = environ;
	if (args[1] == NULL)
	{
		while (*env != NULL)
		{
			ft_printf("declare -x %s\n", *env);
			env++;
		}
		return (0);
	}
	else
	{
		i = 1;
		while (args[i] != NULL)
		{
			name = strtok(args[i], "=");
			value = strtok(NULL, "=");
			if (value == NULL)
				value = "";

			int j;
			j = 0;
			while ( environ[j] != NULL)
				j++;
			char **new_environ = malloc((j + 2) * sizeof(char *));
			int k = 0;
			while ( k < j)
			{
				new_environ[k] = environ[k];
				++k;
			}
			new_environ[j] = malloc(strlen(name) + strlen(value) + 2);
			sprintf(new_environ[j], "%s=%s", name, value);
			new_environ[j + 1] = NULL;
			free(environ);
			environ = new_environ;
			i++;
		}
	}
	return (0);
}
