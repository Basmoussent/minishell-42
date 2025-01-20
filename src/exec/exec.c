/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:13:43 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/20 23:10:41 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void execute_command(t_ast_node *node, char **envp)
{
    char *cmd_path;
    char **args = NULL;

    if (!node || !node->right || !node->right->value)
    {
        write(2, "Invalid command structure\n", 26);
        exit(1);
    }
    args = ft_split(node->right->value, ' ');
    if (!args)
    {
        perror("Error allocating memory for arguments");
        exit(1);
    }
    cmd_path = find_executable(node->value, envp);
    if (!cmd_path)
    {
        free_args(args);
        write(2, "Command not found\n", 18);
        exit(127);
    }
    execve(cmd_path, args, envp);
    perror("execve");
    free(cmd_path);
    free_args(args);
    exit(1);
}

static void execute_pipe(t_ast_node *node, char **envp)
{
    int pipe_fds[2];
    pid_t pid;

    if (!node || !node->left || !node->right)
    {
        write(2, "Invalid pipe structure\n", 23);
        exit(1);
    }

    if (pipe(pipe_fds) == -1)
    {
        perror("pipe");
        exit(1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0)
    {
        dup2(pipe_fds[1], STDOUT_FILENO);
        close(pipe_fds[0]);
        close(pipe_fds[1]);
        exec_ast(node->left, envp);
        exit(1);
    }

    dup2(pipe_fds[0], STDIN_FILENO);
    close(pipe_fds[0]);
    close(pipe_fds[1]);
    waitpid(pid, NULL, 0);
    exec_ast(node->right, envp);
}



static void handle_redirection(t_ast_node *node)
{
    int fd;

    if (!node || !node->right || !node->right->value)
    {
        write(2, "Invalid redirection structure\n", 31);
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
    if (node->type == REDIRECT_INPUT || node->type == HEREDOC)
        dup2(fd, STDIN_FILENO);
    else
        dup2(fd, STDOUT_FILENO);
    close(fd);
}

void	exec_ast(t_ast_node *node, char **envp)
{
	if (!node)
		return;

	if (node->type == PIPE)
		execute_pipe(node, envp);
	else if (node->type == TRUNCATE || node->type == APPEND
		|| node->type == REDIRECT_INPUT || node->type == HEREDOC)
	{
		handle_redirection(node);
		exec_ast(node->left, envp);
	}
	else
		execute_command(node, envp);
}

void	cleanup_and_exit(t_ast_node *root, int status)
{
	free_ast(root);
	exit(status);
}