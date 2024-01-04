/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 23:23:40 by kmb               #+#    #+#             */
/*   Updated: 2024/01/04 22:58:48 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **split_string(char *str, char *delimiters)
{
	int i = 0;
	int arg_count = 0;
	char **args = malloc(MAX_ARGS * sizeof(char *));
	char *arg = NULL;

	if (args == NULL)
	{
		perror("Error allocating memory");
		exit(EXIT_FAILURE);
	}
	arg = str;
	i = 0;
	while ( str[i] != '\0')
	{
		if (ft_strchr(delimiters, str[i]) != NULL)
		{
			str[i] = '\0';
			args[arg_count] = arg;
			arg_count++;
			arg = &str[i + 1];
		}
		i++;
	}
	if (arg != &str[i])
	{
		args[arg_count] = arg;
		arg_count++;
	}

	args[arg_count] = NULL;

	return args;
}

int	main(int argc, char **argv, char **envp)
{
	char	*input = NULL;
	char	**args;

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
		args = split_string(input, DELIMITERS);
		execute_command(args, envp);
		free(input);
		free(args);
	}
	return (0);
}
