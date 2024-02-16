/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/02/16 12:53:47 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"

/*-----------------------------------------INCLUDES------------------*/
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
/*------------------------------------------------------------------------*/
/*-----------------------------------------DEFINES-----------------------*/
# define MAX_INPUT_SIZE 1024
# define MAX_HISTORY 100
# define MAX_ARGS 64
# define DELIMITERS " \t\r\n\a"
/*---------------------------------------------------------------*/

/*-----------------------------------------STRUCTURES---------------*/
typedef struct s_commandhistory
{
	char	*commands[MAX_HISTORY];
	int		index;
}	t_commandhistory;

typedef struct s_expansionData
{
	char	**commands;
	int		i;
	int		*j;
	int		*is_malloced;
}	t_expansiondata;

typedef struct s_parser {
	int		j;
	int		i;
	int		is_single_quote;
	int		is_double_quote;
	int		char_index;
	char	character;
	char	**args;
	char	*command;
	char	*current_token;
}	t_parser;

typedef struct s_command_data {
	char	*commands[7];
	char	var_name[1000];
	int		is_malloced[30];
}	t_command_data;

/*-------------------------------------------------------------*/
extern char			**environ;
/*---------------BUILTINS-------------------------------------------*/
int					cmd_pwd(void);
char				*cmd_history(t_commandhistory *history);
int					cmd_unset(char **args);
void				cmd_env(char **environ);
int					cmd_export(char **args);
int					cmd_echo(char **args);
int					cmd_cd(char **args);
/*---------------HISTORY-------------------------------------*/
void				add_to_history(t_commandhistory *history, char *command);
char				*get_from_history(t_commandhistory *history, int index);
void				destroy_history(t_commandhistory *history);
t_commandhistory	*create_history(void);
void				free_history(t_commandhistory *history);
/*---------------EXEC-----------------------------------------*/
char				*find_command(char *command);
char				*find_command_in_path(char *command, char \
					*path_copy, int max_length);
void				execute_builtin_command(char **args);
int					execute_external_command(char **args);
void				execute_builtin_commandenv(char **args, char **environ);
/*---------------PARSER--------------------------------------------*/
void				parse_command(char *input, t_commandhistory *history);
void				chose_command(char *commands[], int n);
/*---------------LEXER---------------------------------*/
char				**token_pipe_cmd(char *command[], int n);
/*---------------REDIRECTION---------------------------------*/
void				handle_here_document(char *delimiter);
char				**handle_redirection(char **args, int *orig_stdin, \
					int *orig_stdout);
void				chose_redirection(char **args, int i);
/*---------------UTILS-----------------------------------------*/
int					is_single_quote(char *str, int index);
void				restore_io(int orig_stdin, int orig_stdout);
void				handle_sigint(int sig);
void				print_header(void);
void				execute_child_process(char *cmd_path, char **args);
void				free_malloced(char *commands[], int is_malloced[], int i);
int					chose_built_in(char **args);
void				print_environment(char **env);
void				add_to_environment(char **args);
char				**create_new_environment(int j, char *name, char *value);
int					find_env_var(char **args);
void				unset_env_var(int index);
void				chose_command(char *commands[], int n);
void				initialize_expansion_data(t_expansiondata \
					*expansionData, \
					char **commands, int i, int *is_malloced);
void				handle_commands(char **commands, t_expansiondata \
					*expansionData, char *var_name);
void				free_malloced_commands(char **commands, \
					int *is_malloced, int i);
void				handle_builtin_commands(char **args);
void				initialize_variables(int *i, int *fd_in);
void				free_args(char **args);
void				free_environment(char **enviroment, int size);

/*---------------PIPES---------------------------------*/
void				handle_child_process(int fd_in);
void				handle_parent_process(int *fd_in, int fd[2]);
void				chose_pipe(char *commands[], int n);
void				execute_pipe(int fd[2], char **args);

/*---------------VARIABLE EXPANSION---------------------------------*/
void				handle_variable_expansion(char **commands, int *j, \
					int *is_malloced, char *var_name);
#endif
