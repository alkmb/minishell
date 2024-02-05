/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 21:51:32 by akambou           #+#    #+#             */
/*   Updated: 2024/02/05 03:42:48 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_variable_expansion(char **commands, int i, int *j, \
	int *is_malloced, char *var_name)
{
	int		var_name_len;
	char	*var_value;
	char	*new_command;

	var_name_len = 0;
	(*j)++;
	while (ft_isalnum(commands[i][*j]) || commands[i][*j] == '_')
		var_name[var_name_len++] = commands[i][(*j)++];
	var_name[var_name_len] = '\0';
	var_value = getenv(var_name);
	if (var_value != NULL)
	{
		new_command = malloc((ft_strlen(commands[i]) - \
		var_name_len + ft_strlen(var_value) + 2) * sizeof(int));
		ft_strlcpy(new_command, commands[i], *j);
		ft_strlcpy(new_command + *j - var_name_len - 1, \
		var_value, ft_strlen(var_value) + 2);
		ft_strlcpy(new_command + *j - var_name_len - 1 + ft_strlen(var_value), \
		commands[i] + *j, ft_strlen(commands[i] + *j) + 1);
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
