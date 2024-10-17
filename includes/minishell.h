/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:55:04 by pedalexa          #+#    #+#             */
/*   Updated: 2024/10/17 18:47:21 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libraries/Libft/libft.h"

//STRUCTS

typedef enum s_token_type
{
    OPERATOR,
    STRING,
    REDIRECTION,
	PIPE,
    VARIABLE,
	TILDE
} t_token_type;

typedef struct s_token
{
    t_token_type    type;
    char            *content;
}   t_token;

typedef struct	s_env_var
{
	char 				*content;
	char				*name;
	char				*value;
	struct s_env_var	*next;
}	t_env_var;

typedef struct c_list
{
	struct s_env_var	*env;
	struct s_program	*prog;
	char				*path;
	char				**content;
	bool				built_in;
	bool				on_parent;
	int					fd_master[2];
	int					fd[2];
	void				(*ft_exec)(struct c_list **list);
	struct c_list		*next;
	struct c_list		*prev;
}	cmd_list;

typedef struct s_program
{
	char				*input;
	char				**env_sorted;
	char				**init_env;
	int					exit_status;
	struct s_env_var	*env;
	struct c_list		*cmds;
}	t_program;


//PROGRAM FUNCTIONS
void	init_env(t_program *program);
void 	ctrl_slash(int signum);
void 	ctrl_c(int signum);
void 	free_program(t_program *program);
void 	free_program_continue(t_program *program);


//BUILT-IN FUNCTIONS
void	cd(cmd_list **cmd);
void	clear(cmd_list **cmd);
void	echo(cmd_list **cmd);
void	env(cmd_list **cmd);
void	exit_shell(cmd_list **cmd);
void	export_no_args(cmd_list **cmd);
void	export_with_args(cmd_list **cmd);
void	pwd(cmd_list **cmd);
void	unset(cmd_list **cmd);
void	default_exec(cmd_list **cmd);
void	default_exec_bin(cmd_list **cmd);


//PARSE FUNCTIONS
bool	validate_input(t_program *program);
void	parse(t_program *program);
t_token **tokenize(char *input);
t_token *create_token(t_token_type type, const char *content);
t_token **add_token(t_token **tokens, t_token *new_token);
// void 	add_token_if_needed(char *token, int *token_pos, t_token ***tokens, t_token_type token_type);
void	add_token_if_needed(char **token, t_token ***tokens, t_token_type token_type);
void	expand_tokens(t_token **tokens, t_program *program);
void	set_file_descriptors(t_token **tokens, int *i, cmd_list *cmd);
//PARSE UTILS FUNCTIONS
int 	is_operator(char c);
int 	is_whitespace(char c);
void 	free_tokens(t_token **tokens);
void	update_token(char **current_token, char c);


//EXECUTE FUNCTIONS
void	executer(cmd_list *cmd);
char	*find_path(t_env_var *env, char *cmd);
void	execute_redirections(cmd_list *cmd);
void	setup_pipes(cmd_list *cmd);
//EXECUTE UTILS FUNCTIONS
void	set_exec(cmd_list *cmd);
void	check_builtin(cmd_list *cmd);
void	check_process(cmd_list *cmd);
void 	restore_fds(cmd_list *cmd, int og_stdin, int og_stdout);
void 	close_pipe_ends(cmd_list *cmd, int is_parent);
bool 	check_if_full_path(char *s);
void 	exec_error(cmd_list *cmd, char *error);


// UTILS FUNCTIONS
t_env_var	*ft_lstnew_minish(char *content);
void		ft_lstadd_back_minish(t_env_var **lst, t_env_var *new);
int			env_len(char **arr);
char		**copy_array(char **arr);
void		free_arr(char **arr);
void		copy_array_to_list(char **arr, t_env_var **list);
char		**copy_list_to_array(t_env_var **list);
int			ft_lstsize_minish(t_env_var **lst);
void		set_exit_status(cmd_list *cmd, int status);
void		parse_name_value(t_env_var *node);


// DEBUGERS
void	print_tokens1(t_token **tokens);
void	print_cmd_list(t_program *program);

#endif