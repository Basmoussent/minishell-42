/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 16:40:52 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/05 16:45:34 by bdenfir          ###   ########.fr       */
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

typedef struct s_data
{
	char **envp;
} t_data;

// Builtins

int	echo(char *params);
int	handle_echo(char *str);
int	ft_pwd(char **envp);
int	ft_env(char **envp);
void	ft_exit(char *status);
char **copy_envp(char **envp);
void	free_args(char **envp);
int	ft_set_env(char *var, char *value, t_data *data);
int	ft_export(char *str, t_data *data);

#endif
