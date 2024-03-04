/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 01:20:03 by akambou           #+#    #+#             */
/*   Updated: 2024/03/04 20:49:47 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_environment(char **env)
{
	while (*env != NULL)
	{
		ft_printf("declare -x %s\n", *env);
		env++;
	}
}

char	**create_new_environment(int j, char *name, char *value)
{
	int		k;
	char	**new_environ;

	new_environ = malloc((j + 2) * sizeof(char *));
	k = 0;
	while (k < j)
	{
		new_environ[k] = environ[k];
		++k;
	}
	new_environ[j] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	sprintf(new_environ[j], "%s=%s", name, value);
	new_environ[j + 1] = NULL;
	return (new_environ);
}

void	add_to_environment(char **args)
{
	char	*name;
	char	*value;
	int		j;
	int		i;
	char	**new_environ;

	i = 1;
	name = ft_strtok(args[i], "=");
	while (args[i] != NULL)
	{
		value = ft_strtok(NULL, "=");
		if (value == NULL)
			value = "";
		j = 0;
		while (environ[j] != NULL)
			j++;
		i++;
	}
	environ = create_new_environment(j, name, value);
}

int	find_env_var(char **args)
{
	int		i;
	char	*name;
	char	*env_var;

	i = 0;
	while (environ[i])
	{
		env_var = ft_strdup(environ[i]);
		name = ft_strtok(env_var, "=");
		if (ft_strcmp(name, args[1]) == 0)
		{
			free(env_var);
			return (i);
		}
		free(env_var);
		i++;
	}
	return (-1);
}

void	unset_env_var(int index)
{
	int	j;

	j = index;
	while (environ[j])
	{
		environ[j] = environ[j + 1];
		j++;
	}
	free(environ[j]);
}
