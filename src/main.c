/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:23:40 by kmb               #+#    #+#             */
/*   Updated: 2023/12/20 23:38:32 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char	*input = NULL;
	char	*args[MAX_ARGS];
	int		i;
	if (argc != 1)
	{
		fprintf(stderr, "Usage: %s\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		ft_printf("%s@->$ ", getenv("USER"));
		input = get_next_line(STDIN_FILENO);
		if (input == NULL)
		{
			perror("Error reading input");
			exit(EXIT_FAILURE);
		}
		i = 0;
		args[i] = strtok(input, DELIMITERS);
		while (args[i] != NULL)
			args[++i] = strtok(NULL, DELIMITERS);
		execute_command(args, envp);
		free(input);
	}
	return (0);
}
