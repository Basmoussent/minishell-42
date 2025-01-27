/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:40:52 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/27 14:52:57 by akassous         ###   ########.fr       */
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

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"
#define COLOR_CYAN_BOLD "\033[1;36m"
#define COLOR_YELLOW_BOLD  "\033[1;33m"
#define TYPE_COLOR "\033[1;34m"
#define VALUE_COLOR "\033[1;32m"
#define INDENT_COLOR "\033[0;33m"
#define HERE_DOC_TMP ".heredoc_tmp"

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

typedef struct s_data
{
	char	**envp;
	int		ast;
}	t_data;

// Builtins
int		ft_echo(char *str);
int		ft_pwd(t_data *data);
int		ft_env(char **envp);
int		ft_exit(char *input);
int		ft_unset(char *input, t_data *data);
int		ft_export(char *str, t_data *data);
int		ft_cd(char *path, t_data *data);
int		ft_ast(t_data *data);

// ENV
int		is_valid_varname(char *var);
void	ft_process_input(char *input, char *buffer);
char	**copy_envp(char **envp);
int		ft_set_env(char *var, char *value, t_data *data);

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

// EXEC
int		heredoc_logic(char *delimiter);
void	exec_ast(t_ast_node *node, t_data *data);
void	reset_stream(int saved_stdin, int saved_stdout);
void	handle_redirection(t_ast_node *node);
int		exec_builtin(t_ast_node *node, t_data *data);
int		is_builtin(t_ast_node *node);
void	redirect_output(t_ast_node * node, int fd);

// UTILS
bool	validate_command(const char *cmd);
void	cleanup_and_exit(t_ast_node *root, t_data *data, char **args, char *cmd_path, int status);

//TEST SUITE
int ft_exit_test(void);
int ft_echo_test(void);
int ft_lexer_test(int argc, char **argv, char **envp);

#endif