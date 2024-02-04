/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:12:49 by kmb               #+#    #+#             */
/*   Updated: 2024/02/04 04:00:18 by akambou          ###   ########.fr       */
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
		ft_printf("%s", args[i]);
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
	if (args[1] != NULL)
	{
		if (chdir(args[1]) != 0)
		{
			perror(args[1]);
			return (127);
		}
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

	if (args[1] != NULL)
	{
		i = 0;
		while (environ[i])
		{
			if (ft_strcmp(environ[i], args[1]) == 0)
			{
				free(environ[i]);  // Free the memory for the variable
				for (j = i; environ[j]; j++)
					environ[j] = environ[j + 1];
				break ;
			}
			i++;
		}
	}
	else
	{
		ft_printf("Usage: unset variable_name\n");
		return (127);
	}
	return (0);
}

int	cmd_export(char **args)
{
	char	**env;
	char	*name;
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
			name = args[i];
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
			new_environ[j] = strdup(name);
			new_environ[j + 1] = NULL;
			free(environ);
			environ = new_environ;
			i++;
		}
	}
	return (0);
}
