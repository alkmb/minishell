/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 00:44:13 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// function to handle variable expansion
void	handle_commands(char **commands, t_expansiondata \
*expansionData, char *var_name)
{
	int	j;

	j = 0;
	// loop through the command and expand the variables
	while (commands[expansionData->i][j] != '\0')
	{
		// if the character is a dollar sign and not in single quotes
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

void	chose_command(char *commands[], int n)
{
	if (n < 0)
		return ;
	else
		chose_pipe(commands, n);
}

void	parse_command(char *input, t_commandhistory *history)
{
	int					i;
	char				*commands[7];
	char				var_name[1000];
	int					is_malloced[30];
	t_expansiondata		expansiondata;

	i = 0;
	is_malloced[0] = 0;
	initialize_expansion_data(&expansiondata, commands, i, is_malloced);
	add_to_history(history, input);
	// split the input into commands
	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		// expand the variables in the command
		handle_commands(commands, &expansiondata, var_name);
		i++;
		commands[i] = ft_strtok(NULL, "|");
	}
	// choose the command to execute
	chose_command(commands, i - 1);
	free_malloced_commands(commands, is_malloced, i);
}
