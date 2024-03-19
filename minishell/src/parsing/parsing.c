/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:58:05 by kmb               #+#    #+#             */
/*   Updated: 2024/03/19 06:31:39 by kmb              ###   ########.fr       */
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
	if (handle_exception(input) == 0)
		return ;
	commands[i] = ft_strtok(input, "|");
	while (commands[i] != NULL)
	{
		handle_commands(commands, &expansiondata, var_name);
		i++;
		commands[i] = ft_strtok(NULL, "|");
	}
	chose_command(commands, i - 1);
	free_malloced_commands(commands, is_malloced, i);
}
