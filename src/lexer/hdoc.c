/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hdoc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:37:53 by gprada-t          #+#    #+#             */
/*   Updated: 2024/05/09 19:24:15 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	print_heredoc(char *input_buffer)
{
	if (input_buffer != NULL)
	{
		ft_printf("Here document content:\n%s\n", input_buffer);
		free(input_buffer);
	}
}

void	handle_here_document(char *delimiter)
{
	char	*line;
	char	*input_buffer;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	ft_printf("> ");
	if (!delimiter)
		return (printf("Error: no delimiter\n"), (void)(0));
	line = "";
	while (1)
	{
		line = readline("");
		if (!line)
			exit(1);
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		check_buffer_size(&input_buffer, line);
		free(line);
		ft_printf("> ");
	}
	print_heredoc(input_buffer);
}
