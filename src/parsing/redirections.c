/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 09:09:46 by kmb               #+#    #+#             */
/*   Updated: 2024/04/17 09:38:21 by gprada-t         ###   ########.fr       */
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
		*input_buffer = ft_strdup(line);
	else
	{
		current_len = ft_strlen(*input_buffer);
		new_len = current_len + ft_strlen(line) + 2;
		*input_buffer = ft_realloc(*input_buffer, new_len);
		ft_strlcat(*input_buffer, "\n", new_len);
		ft_strlcat(*input_buffer, line, new_len);
	}
}

static void	redirect_or_append(char **args, int i, int *fd)
{
	if (ft_strcmp(args[i], ">") == 0)
		*fd = open(args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else
		*fd = open(args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	dup2(*fd, STDOUT_FILENO);
}

void	chose_redirection(char **args, int i)
{
	int	fd;

	fd = 0;
	if (args[i] == NULL || args[i + 1] == NULL)
	{
		printf("Error: syntax error\n");
		exit(1);
	}
	if (ft_strcmp(args[i], ">") == 0 || ft_strcmp(args[i], ">>") == 0)
	{
		redirect_or_append(args, i, &fd);
	}
	else if (ft_strcmp(args[i], "<") == 0)
	{
		fd = open(args[i + 1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else if (ft_strcmp(args[i], "<<") == 0)
	{
		handle_here_document(args[i + 1]);
		ft_crazy_free(args);
		exit(1);
	}
	else if (!fd)
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
