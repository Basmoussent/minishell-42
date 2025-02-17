/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:45:47 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/29 15:21:22 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_command(t_ast_node *node, t_data *data)
{
	pid_t	pid;
	char	**args;

	if (!node || !node->value)
		handle_error("Invalid command structure");
	args = prepare_args(node);
	if (is_builtin(node))
	{
		data->status = exec_builtin(node, data);
		free_args(args);
		return ;
	}
	pid = fork();
	if (pid == -1)
		handle_error("fork");
	if (pid == 0)
		handle_command_child(node, data, args);
	handle_command_parent(data, pid, args);
}

static void	execute_pipe(t_ast_node *node, t_data *data)
{
	int		pipe_fds[2];
	pid_t	left_pid;
	pid_t	right_pid;

	if (!node || !node->left || !node->right)
	{
		write(2, "Invalid pipe structure\n", 23);
		cleanup_and_exit(node, data, NULL, NULL);
	}
	if (pipe(pipe_fds) == -1)
		handle_error("pipe");
	left_pid = fork();
	if (left_pid == -1)
		handle_error("fork");
	if (left_pid == 0)
		execute_child(node, data, pipe_fds);
	right_pid = fork();
	if (right_pid == -1)
		handle_error("fork");
	if (right_pid == 0)
		handle_right_child(node, data, pipe_fds);
	handle_pipe_parent(data, pipe_fds, left_pid, right_pid);
}

void	exec_ast(t_ast_node *node, t_data *data)
{
	int	saved_stdin;
	int	saved_stdout;

	if (!node || !data)
		return ;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (node->type == PIPE)
		execute_pipe(node, data);
	else if (node->type == TRUNCATE || node->type == APPEND
		|| node->type == REDIRECT_INPUT || node->type == HEREDOC)
	{
		handle_redirection(node, data);
		exec_ast(node->left, data);
		reset_stream(saved_stdin, saved_stdout);
	}
	else
		execute_command(node, data);
}
