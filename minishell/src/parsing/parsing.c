/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/03/04 15:17:29 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_commands(char **commands, t_expansiondata \
*expansionData, char *var_name)
{
	int	j;

	j = 0;
	while (commands[expansionData->i][j] != '\0')
	{
		if (commands[expansionData->i][j] == '$'
			&& (is_single_quote(commands[expansionData->i], j) == 0))
			handle_variable_expansion(commands, &j, \
				expansionData->is_malloced, var_name);
		else
			j++;
	}
	free_malloced_commands(expansionData->commands, \
		expansionData->is_malloced, expansionData->i);
}

int	chose_command(char *commands[], int n)
{
	int	status;

	if (n < 0)
		return status;
	else
		status = chose_pipe(commands, n);
	return status;
}

int	parse_command(char *input, t_commandhistory *history)
{
	int					i;
	char				**commands;
	char				var_name[1000];
	int					is_malloced[30];
	t_expansiondata		expansiondata;
	int					status;

	i = 0;
	is_malloced[0] = 0;
	commands = malloc(30 * sizeof(char *));
	initialize_expansion_data(&expansiondata, commands, i, is_malloced);
	add_to_history(history, input);
	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		handle_commands(commands, &expansiondata, var_name);
		i++;
		commands[i] = ft_strtok(NULL, "|");
	}
	status = chose_command(commands, i - 1);
	free_malloced_commands(commands, is_malloced, i);
	free(commands);
	return status;
}
