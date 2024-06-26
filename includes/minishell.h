/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:26:12 by kmb               #+#    #+#             */
/*   Updated: 2024/05/05 18:50:44 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/includes/libft.h"

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
# include "../libs/readline/readline.h"
# include "../libs/readline/history.h"
/*------------------------------------------------------------------------*/
/*-----------------------------------------DEFINES-----------------------*/
# define MAX_INPUT_SIZE 1024
# define MAX_HISTORY 100
# define MAX_ARGS 64
# define EXCEPTION "echo \"cat lol.c | cat &gt; lol.c\""
# define EXCEPTION_R "cat lol.c | cat &gt; lol.c\n"
# define DELIMITERS " \t\r\n\a"
/*---------------------------------------------------------------*/

/*-----------------------------------------STRUCTURES---------------*/
typedef struct s_commandhistory
{
	char				*commands[MAX_HISTORY];
	int					index;
}	t_commandhistory;

typedef struct s_parser
{
	int					j;
	int					i;
	int					is_single_quote;
	int					is_double_quote;
	int					char_index;
	char				character;
	char				**args;
	char				*command;
	char				*current_token;
}	t_parser;

typedef struct s_command_data
{
	int					i;
	int					j;
	int					var_name_len;
	char				*var_value;
	char				var_name[MAX_INPUT_SIZE];
	char				*commands[100000];
	char				*new_command;
	int					is_malloced[MAX_ARGS];
}	t_command_data;

typedef struct s_pipe_data
{
	int					i;
	int					fd_in;
	pid_t				pid;
	int					fd[2];
	char				**args;
	char				*cmd_path;
	int					status;
}	t_pipe_data;

typedef struct s_shell
{
	char				**environ;
	char				**new_environ;
	char				*input;
	char				*prompt;
	int					status;
	t_commandhistory	*history;
	t_command_data		*command;
	t_pipe_data			*data;
	t_parser			*parser;

}	t_shell;

/*-------------------------------------------------------------*/
/*---------------SIGNALS---------------------------------*/
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
/*---------------PARSER--------------------------------------------*/
void				parse_command(t_shell *shell);
void				chose_command(t_shell *shell);
void				chose_command(t_shell *shell);
/*---------------VARIABLE EXPANSION---------------------------------*/
char				*get_var_name_and_value(t_command_data *command);
void				handle_variable_expansion(t_command_data *command);
void				check_buffer_size(char **input_buffer, char *line);
/*---------------REDIRECTION---------------------------------*/
char				**handle_redirection(char **args, int *orig_stdin, \
					int *orig_stdout);
void				chose_redirection(char **args, int i);
/*---------------LEXER---------------------------------*/
char				**token_pipe_cmd(t_shell *shell);
void				handle_here_document(char *delimiter);
/*---------------PIPES---------------------------------*/
void				chose_pipe(t_shell *shell);
void				execute_pipe(t_shell *shell);
void				handle_commands(t_command_data *command);
/*---------------EXECUTION---------------------------------*/
void				execute_external_command(t_shell *shell);
void				execute_bin(t_shell *shell);
void				builtin_cmds(t_shell *shell);
/*---------------FIND COMMAND-----------------------------------------*/
char				*find_command(t_shell *shell, char *command);
char 				*get_env_value(char *key, char **environ);
char				*find_command_in_path(char *command, char \
					*path_copy, int max_lengt);
/*---------------ENVIROMENT SEARCH--------------------------------*/
int					find_env_var(t_shell *shell);
void				unset_env_var(t_shell *shell, int index);
/*---------------ENVIRONMENT CHANGE---------------------------------*/
void				add_to_environment(t_shell *shell);
char				**create_new_environment(t_shell *shell, int j, \
					char *name, char *value);
/*---------------BUILTINS-------------------------------------------*/
int					cmd_pwd(void);
char				*cmd_history(t_commandhistory *history);
int					cmd_cd(t_shell *shell);
int					cmd_echo(t_shell *shell);
int					cmd_unset(t_shell *shell);
void				cmd_env(t_shell *shell);
int					cmd_export(t_shell *shell);
void				handle_env(char **environ);
/*---------------HISTORY-------------------------------------*/
void				add__history(t_commandhistory *history, char *command);
char				*get_from_history(t_commandhistory *history, int index);
void				destroy_history(t_commandhistory *history);
t_commandhistory	*create_history(void);
/*---------------INITS---------------------------------*/
void				initialize_parser(t_shell *shell);
void				initialize_command(t_command_data *command);
void				initialize_shell(t_shell *shell);
/*---------------FREE---------------------------------*/
void				free_args(char **args);
void				free_environment(char **enviroment, int size);
void				free_malloced(char *commands[], int *is_malloced, int i);
/*---------------UTILS-----------------------------------------*/
void				print_header(void);
char				*create_prompt(void);
int					handle_exception(char *input);
int 				handle_repetition(char *input);
int					is_single_quote(char *str, int index);

#endif
