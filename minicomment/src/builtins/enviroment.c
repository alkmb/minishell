/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enviroment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 01:20:03 by akambou           #+#    #+#             */
/*   Updated: 2024/03/19 00:40:14 by kmb              ###   ########.fr       */
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

// FUNCTION TO CREATE A NEW ENVIRONMENT
char	**create_new_environment(int j, char *name, char *value)
{
	int		k;
	char	**new_environ;

	// ALLOCATE MEMORY FOR THE NEW ENVIRONMENT
	new_environ = malloc((j + 2) * sizeof(char *));
	k = 0;
	// COPY THE OLD ENVIRONMENT TO THE NEW ENVIRONMENT
	while (k < j)
	{
		new_environ[k] = strdup(environ[k]);
		++k;
	}
	// ALLOCATE MEMORY FOR THE NEW ENVIRONMENT
	new_environ[j] = malloc(ft_strlen(name) + ft_strlen(value) + 2);
	// COPY THE NAME AND VALUE TO THE NEW ENVIRONMENT
	strcpy(new_environ[j], name);
	strcat(new_environ[j], "=");
	strcat(new_environ[j], value);
	new_environ[j + 1] = NULL;
	return (new_environ);
}

// FUNCTION TO ADD TO THE ENVIRONMENT
void	add_to_environment(char **args)
{
	char	*name;
	char	*value;
	int		j;
	int		i;

	i = 1;
	// TOKENIZE THE ARGUMENTS BY THE EQUAL SIGN TO GET THE NAME AND VALUE
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
	// CREATE A NEW ENVIRONMENT
	environ = create_new_environment(j, name, value);
}

int	find_env_var(char **args)
{
	int		i;
	char	*name;
	char	*env_var;

	i = 0;
	// FIND THE ENVIRONMENT VARIABLE
	while (environ[i])
	{
		// TOKENIZE THE ENVIRONMENT VARIABLE BY THE EQUAL SIGN TO GET THE NAME
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
	int		j;
	char	*temp;

	// REMOVE THE ENVIRONMENT VARIABLE
	temp = environ[index];
	j = index;
	while (environ[j])
	{
		environ[j] = environ[j + 1];
		j++;
	}
	// FREE THE MEMORY FROM THE FIRST ENVIRONMENT VARIABLE
	free(temp);
}
