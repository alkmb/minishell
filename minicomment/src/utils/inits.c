/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:14:07 by akambou           #+#    #+#             */
/*   Updated: 2024/03/02 21:51:09 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(int *i, int *fd_in)
{
	*fd_in = 0;
	*i = 0;
}

void	initialize_expansion_data(t_expansiondata *expansionData, \
char **commands, int i, int *is_malloced)
{
	expansionData->commands = commands;
	expansionData->i = i;
	expansionData->j = 0;
	expansionData->is_malloced = is_malloced;
}

t_parser	initialize_parser(char *commands[], int n)
{
	t_parser	parser;

	parser.j = 0;
	parser.i = 0;
	parser.is_single_quote = 0;
	parser.is_double_quote = 0;
	parser.char_index = 0;
	parser.args = (char **)malloc(MAX_ARGS * sizeof(char *));
	parser.command = commands[n];
	parser.current_token = malloc(1000 * sizeof(char));
	return (parser);
}
