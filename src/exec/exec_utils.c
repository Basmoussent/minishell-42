/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:45:47 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/25 18:15:52 by bdenfir          ###   ########.fr       */
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
	char	*tmp;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (path && access(path, X_OK) == 0)
			return (free_args(paths), path);
		free(path);
	}
	return (free_args(paths), NULL);
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

	cmd_path = NULL;
	get_cmd_path(node, data->envp, &cmd_path, args);
	if (ft_strncmp(args[0], "./minishell", 12) != 0)
		signal(SIGQUIT, SIG_DFL);
	execve(cmd_path, args, data->envp);
	perror("execve");
	cleanup_and_exit(node, data, args, cmd_path);
}

void	handle_command_parent(pid_t pid, char **args)
{
	int	status;

	free_args(args);
	waitpid(pid, &status, 0);
	if ((status & 0x7f) == 0)
		g_signal_received = (status & 0xff00) >> 8;
	else
		g_signal_received = 128 + (status & 0x7f);
}
