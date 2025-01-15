/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:40:52 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/15 16:12:03 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdbool.h>

#define COLOR_RESET   "\033[0m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"

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

typedef struct s_data
{
	char	**envp;
}	t_data;

// Builtins

void		ft_echo(char *str);
int		handle_echo(char *params, int newline);	
int		ft_pwd(char **envp);
int		ft_env(char **envp);
int		ft_exit(char *input);


char	**copy_envp(char **envp);
void	free_args(char **envp);
int		ft_set_env(char *var, char *value, t_data *data);
int		ft_export(char *str, t_data *data);



//TEST SUITE

int ft_exit_test(void);
int ft_echo_test(void);

#endif
