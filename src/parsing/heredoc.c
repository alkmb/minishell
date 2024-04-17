/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 09:37:53 by gprada-t          #+#    #+#             */
/*   Updated: 2024/04/17 09:38:15 by gprada-t         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handle_siginthc(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		exit(1);
	}
	else if (sig == SIGQUIT)
	{
		printf("\b\b  \b\b");
		fflush(stdout);
	}
}

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

	signal(SIGINT, handle_siginthc);
	signal(SIGQUIT, handle_siginthc);
	ft_printf("> ");
	if (!delimiter)
		return (printf("Error: no delimiter\n"), (void)(0));
	line = "";
	signal(SIGQUIT, SIG_IGN);
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
