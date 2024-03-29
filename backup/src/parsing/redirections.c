/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:09:46 by kmb               #+#    #+#             */
/*   Updated: 2024/03/02 22:23:12 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_buffer_size(char **input_buffer, char *line)
{
	size_t	current_len;
	size_t	new_len;

	current_len = 0;
	new_len = 0;
	if (*input_buffer == NULL)
		*input_buffer = strdup(line);
	else
	{
		current_len = strlen(*input_buffer);
		new_len = current_len + strlen(line) + 2;
		*input_buffer = realloc(*input_buffer, new_len);
		ft_strlcat(*input_buffer, "\n", new_len);
		ft_strlcat(*input_buffer, line, new_len);
	}
}

void	handle_here_document(char *delimiter)
{
	char	*line;
	char	*input_buffer;

	input_buffer = NULL;
	ft_printf("> ");
	if (!delimiter)
		return (printf("Error: no delimiter\n"), (void)(0));
	while (line != NULL)
	{
		line = readline("");
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		check_buffer_size(&input_buffer, line);
		free(line);
		ft_printf("> ");
	}
	if (input_buffer != NULL)
	{
		ft_printf("Here document content:\n%s\n", input_buffer);
		free(input_buffer);
	}
}

void	chose_redirection(char **args, int i)
{
	int	fd;

	if (ft_strcmp(args[i], ">") == 0)
	{
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (ft_strcmp(args[i], "<") == 0)
	{
		fd = open(args[i + 1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (ft_strcmp(args[i], ">>") == 0)
	{
		fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	else if (ft_strcmp(args[i], "<<") == 0)
	{
		handle_here_document(args[i + 1]);
		exit(EXIT_SUCCESS);
	}
	if (fd != -1)
		close(fd);
}

char	**handle_redirection(char **args, int *orig_stdin, int *orig_stdout)
{
	int	i;
	int	j;

	i = 0;
	*orig_stdin = dup(STDIN_FILENO);
	*orig_stdout = dup(STDOUT_FILENO);
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], "<") == 0
			|| ft_strcmp(args[i], ">>") == 0 || ft_strcmp(args[i], "<<") == 0)
		{
			chose_redirection(args, i);
			j = i;
			while (args[j] != NULL)
			{
				free(args[j]);
				args[j] = args[j + 2];
				j++;
			}
		}
		else
			i++;
	}
	return (args);
}
