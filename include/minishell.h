/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:40:52 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/12 14:41:21 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_CYAN_BOLD "\033[1;36m"
#define COLOR_YELLOW_BOLD  "\033[1;33m"
#define TYPE_COLOR "\033[1;34m"
#define VALUE_COLOR "\033[1;32m"
#define INDENT_COLOR "\033[0;33m"\

#define HERE_DOC_TMP ".heredoc_tmp"
#define BLANK_FILE ".blank_tmp"


extern volatile int g_signal_received;

enum
{
	KO = 1,
	OK = 0
};

enum	s_token {
	NONE = 0,
	PIPE = 1,
	TRUNCATE = 2,
	APPEND = 3,
	REDIRECT_INPUT = 4,
	HEREDOC = 5
};

typedef struct s_ast_node
{
	enum s_token type;
	char *value;
	struct s_ast_node *left;
	struct s_ast_node *right;
}	t_ast_node;

typedef struct s_token_processing
{
    char 	**tokens;
    char 	**filtered_tokens;
	char	**ignored_tokens;
    int 	i;
    int 	j;
	int		k;
    char 	*last_redirection;
    char 	*last_target;
} t_token_processing;

typedef struct s_data
{
	char	**envp;
	char	**export;
	int		ast;
	char	*hd_file;
	t_ast_node  *current_ast;
	char 	**tokens;
	char 	*input;
	int 	status;
}	t_data;

// Builtins
int		ft_echo(char *str);
int		ft_pwd(t_data *data);
int		ft_env(char **envp);
int		ft_exit(char *input, t_data *data);
int		ft_unset(char *input, t_data *data);
int		ft_export(char *str, t_data *data);
int		ft_cd(char *path, t_data *data);
int		ft_ast(t_data *data);

// ENV
int		is_valid_varname(char *var);
void	ft_process_input(char *input, char *buffer);
char	**copy_envp(char **envp);
int		ft_set_env(char *var, char *value, t_data *data);
char	**copy_export_list(char **envp);

// LEXER
int			is_space(char c);
char		*is_quote(char *end);
size_t		ft_strnlen(const char *s, size_t maxlen);
char		*ft_strndup(const char *s, size_t n);
char		**free_tokens(char **tokens);
void		free_args(char **args);
char 		**split_whitespace(char *input);
int			count_tokens(char *input);
t_ast_node	*lexing(char *input, t_data *data);
char		*trim_input(char *input);
char		*get_next_quote(char *input, int double_qte);
t_ast_node 	*parse_tokens(char **tokens, t_data *data);
t_ast_node 	*create_ast_node(enum s_token type, char *value);
char		*expand_all_variables(char *input, t_data *data);
char		*get_env_value(char *name, t_data *data);
void		free_ast(t_ast_node *node);
void print_ast(t_ast_node *node, const char *prefix, int is_left);
void compress_ast(t_ast_node *node);
void split_ast(t_ast_node *node);
void clean_redirections(t_ast_node *node) ;
char **filter_tokens(char **tokens);
int	is_speci(char *token);
int	count_tokens_array(char **tokens);
char	**allocate_filtered_tokens(char **tokens);


char	**allocate_ignored_tokens(char **tokens);

// EXEC
int		heredoc_logic(char *delimiter, t_data *data);
void	exec_ast(t_ast_node *node, t_data *data);
void	reset_stream(int saved_stdin, int saved_stdout);
void	handle_redirection(t_ast_node *node, t_data *data);
int		exec_builtin(t_ast_node *node, t_data *data);
int		is_builtin(t_ast_node *node);
void	redirect_output(t_ast_node * node, int fd);

// UTILS
bool	validate_command(const char *cmd);
void	cleanup_and_exit(t_ast_node *root, t_data *data, char **args, char *cmd_path, int status);
void    handle_signals(int signum);

//TEST SUITE
int ft_exit_test(void);
int ft_echo_test(void);
int ft_lexer_test(int argc, char **argv, char **envp);

void	cleanup_shell(t_data *data);

#endif