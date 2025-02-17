/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:45:47 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/17 15:37:01 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_error(const char *msg, int status)
{
	perror(msg);
	exit(status);
}

char	*find_executable(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH", 4) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
		{
			free_args(paths);
			return (path);
		}
		free(path);
	}
	free_args(paths);
	return (0);
}

char	**prepare_args(t_ast_node *node)
{
	char	**args;
	char	*temp;
	char	*str;

	if (node->right && node->right->value)
	{
		temp = ft_strjoin(node->value, " ");
		str = ft_strjoin(temp, node->right->value);
		args = ft_split(str, ' ');
		free(str);
		free(temp);
	}
	else
	{
		args = malloc(2 * sizeof(char *));
		if (!args)
			handle_error("Error allocating memory for arguments", 1);
		args[0] = ft_strdup(node->value);
		args[1] = NULL;
	}
	return (args);
}

void	handle_command_child(t_ast_node *node, t_data *data, char **args)
{
	char	*cmd_path;

	handle_signals_child();
	cmd_path = NULL;
	get_cmd_path(node, data->envp, &cmd_path, args);
	execve(cmd_path, args, data->envp);
	perror("execve");
	cleanup_and_exit(node, data, args, cmd_path);
}

void	handle_command_parent(t_data *data, pid_t pid, char **args)
{
	free_args(args);
	waitpid(pid, &data->status, 0);
	if ((data->status & 0x7f) == 0)
		data->status = (data->status & 0xff00) >> 8;
	else
		data->status = 128 + (data->status & 0x7f);
}
