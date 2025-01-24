/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 19:49:12 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/24 16:49:23 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to handle heredoc
void	handle_redirection(t_ast_node *node)
{
	int	fd;

	if (!node || !node->right || !node->right->value)
	{
		write(2, "Syntax error near unexpected token ", 35);
		write(2, node->value, ft_strlen(node->value));
		write(2, "\n", 1);
		exit(1);
	}
	if (node->type == TRUNCATE)
		fd = open(node->right->value, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->type == APPEND)
		fd = open(node->right->value, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (node->type == REDIRECT_INPUT)
		fd = open(node->right->value, O_RDONLY);
	else if (node->type == HEREDOC)
		fd = heredoc_logic(node->right->value);
	else
		return ;
	if (fd == -1)
	{
		perror("Error opening file");
		exit(1);
	}
	redirect_output(node, fd);
}

// Function to cehck if a cmd is a builtin
int is_builtin(t_ast_node *node)
{
	if (!node || !node->value)
		return (0);
	if (ft_strncmp(node->value, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(node->value, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(node->value, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(node->value, "export", 6) == 0)	
		return (1);
	if (ft_strncmp(node->value, "unset", 5) == 0)	
		return (1);
	if (ft_strncmp(node->value, "env", 3) == 0)	
		return (1);
	if (ft_strncmp(node->value, "exit", 4) == 0)	
		return (1);
	if (ft_strncmp(node->value, "ast", 3) == 0)	
		return (1);
	return (0);
}

// Function to execute a builtin command
int exec_builtin(t_ast_node *node, t_data *data)
{
	char *arg;

	if (!node || !node->value)
		return (0);
	arg = "";
	if (node->right && node->right->value)
		arg = node->right->value;
	if (ft_strncmp(node->value, "echo", 4) == 0)
		return (ft_echo(arg));
	if (ft_strncmp(node->value, "cd", 2) == 0)
		return (ft_cd(arg, data));
	if (ft_strncmp(node->value, "pwd", 3) == 0)
		return (ft_pwd(data));
	if (ft_strncmp(node->value, "export", 6) == 0)	
		return (ft_export(arg, data));
	if (ft_strncmp(node->value, "unset", 5) == 0)	
		return (ft_unset(arg, data));
	if (ft_strncmp(node->value, "env", 3) == 0)	
		return (ft_env(data->envp));
	if (ft_strncmp(node->value, "exit", 4) == 0)	
		return (ft_exit(arg));
	if (ft_strncmp(node->value, "ast", 3) == 0)	
		return (ft_ast(data));
	return (0);
}
