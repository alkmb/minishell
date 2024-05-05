/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 09:43:14 by kmb               #+#    #+#             */
/*   Updated: 2024/05/05 14:39:16 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	t_shell				shell;

	initialize_shell(&shell);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	shell.history = create_history();
	print_header();
	while (1)
	{
		shell.prompt = create_prompt();
		shell.input = readline(shell.prompt);
		free(shell.prompt);
		if (shell.input && *shell.input)
			add_history(shell.input);
		if (shell.input == NULL)
			exit(EXIT_FAILURE);
		initialize_command(shell.command);
		parse_command(&shell);
		free(shell.input);
	}
	return (shell.status);
}
