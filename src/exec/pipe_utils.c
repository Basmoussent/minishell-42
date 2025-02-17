/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:45:47 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/29 15:21:22 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_ast_node *node, t_data *data, int *pipe_fds)
{
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	exec_ast(node->left, data);
	exit(1);
}

void	handle_right_child(t_ast_node *node, t_data *data, int *pipe_fds)
{
	close(pipe_fds[1]);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	exec_ast(node->right, data);
	exit(1);
}

void	handle_pipe_parent(t_data *data, int *pipe_fds,
	pid_t left_pid, pid_t right_pid)
{
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	waitpid(left_pid, NULL, 0);
	waitpid(right_pid, &data->status, 0);
	if ((data->status & 0x7f) == 0)
		data->status = (data->status & 0xff00) >> 8;
	else
		data->status = 128 + (data->status & 0x7f);
}
