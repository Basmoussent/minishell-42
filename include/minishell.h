/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:40:52 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/14 22:47:49 by akassous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"

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

int		ft_echo(char *str);
int		handle_echo(char *params, int newline);	
int		ft_pwd(char **envp);
int		ft_env(char **envp);
int		ft_exit(char *input);


char	**copy_envp(char **envp);
void	free_args(char **envp);
int		ft_set_env(char *var, char *value, t_data *data);
int		ft_export(char *str, t_data *data);

#endif
