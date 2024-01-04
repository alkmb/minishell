/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2023/12/21 02:36:16 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/includes/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

extern char	**environ;

# define MAX_INPUT_SIZE 1024
#define MAX_ARGS 64
#define DELIMITERS " \t\r\n\a"

void	free_split(char **split);
char	*get_envp(char *n_envp, char **envp);
char	*get_path(char *cmd, char **envp);
int		exec_command(int argc, char **argv, char **envp);
void	exec_cmd(char *argv, char **envp);
void	chose_command(int *fd_old, int argc, char **argv, char **envp);
void	cmd_unset(char **args);
void	cmd_cd(char **args);
void	cmd_env(char **environ);
void	cmd_export(char **args);
void	cmd_external(char **args);
void	execute_first_command(int *fd, char **argv, char **envp);
void execute_mid_command(int *fd_old, int *fd_new, char **argv, char **envp);
void	execute_last_command(int *fd_old, int argc, char **argv, char **envp);




#endif
