/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:51:32 by akambou           #+#    #+#             */
/*   Updated: 2024/03/19 00:38:14 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// FUNCTION TO HANDLE VARIABLE EXPANSION
char	*get_var_name_and_value(char **commands, int i, int *j, char *var_name)
{
	int	var_name_len;

	var_name_len = 0;

	// GET THE VARIABLE NAME
	while (ft_isalnum(commands[i][*j]) || commands[i][*j] == '_')
		var_name[var_name_len++] = commands[i][(*j)++];
	var_name[var_name_len] = '\0';
	return (getenv(var_name));
}

// FUNCTION TO HANDLE VARIABLE EXPANSION
void	handle_variable_expansion(char **commands, int *j, \
	int *is_malloced, char *var_name)
{
	int		var_name_len;
	char	*var_value;
	int		i;
	char	*new_command;

	i = 0;
	(*j)++;
	// GET THE VARIABLE NAME AND VALUE
	var_value = get_var_name_and_value(commands, i, j, var_name);
	if (var_value != NULL)
	{
		// ALLOCATE MEMORY FOR THE NEW COMMAND
		var_name_len = ft_strlen(var_name);
		new_command = malloc((ft_strlen(commands[i]) - \
		var_name_len + ft_strlen(var_value)) * sizeof(char));
		// COPY THE COMMAND TO THE NEW COMMAND
		ft_strlcpy(new_command, commands[i], *j);
		ft_strlcpy(new_command + *j - var_name_len - 1, \
		var_value, ft_strlen(var_value));
		free_malloced(commands, is_malloced, i);
		commands[i] = new_command;
		is_malloced[i] = 1;
	}
	else
		return ;
}

int	cmd_export(char **args)
{
	if (args[1] == NULL)
	{
		print_environment(environ);
		return (0);
	}
	else
	{
		add_to_environment(args);
	}
	return (0);
}
