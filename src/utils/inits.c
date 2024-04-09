/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 02:14:07 by akambou           #+#    #+#             */
/*   Updated: 2024/04/08 09:40:59 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	initialize_variables(int *i, int *fd_in)
{
	*fd_in = 0;
	*i = 0;
}

void	initialize_command_data(t_command_data *command)
{
	command->i = 0;
	command->j = 0;
	command->is_malloced[0] = 0;
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
