/* ************************************************************************** */
/*					*/
/*			  :::	::::::::   */
/*   exec.c   :+:   :+:	:+:   */
/*			  +:+ +:+	+:+   */
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+  */
/*			+#+#+#+#+#+   +#+  */
/*   Created: 2025/01/20 20:13:43 by bdenfir		   #+#  #+#	*/
/*   Updated: 2025/01/21 18:57:30 by bdenfir		  ###   ########.fr */
/*					*/
/* ************************************************************************** */

#include "minishell.h"

// Function to handle error
static void	handle_error(const char *msg)
{
	perror(msg);
	exit(1);
}

// Function to find the executable
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

// Function to prepare argument list for execve
static char **prepare_args(t_ast_node *node)
{
	char **args;
	char *temp;
	char *str;

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
			handle_error("Error allocating memory for arguments");
		args[0] = ft_strdup(node->value);
		args[1] = NULL;
	}
	return (args);
}

void get_cmd_path(t_ast_node *node, char **envp, char **cmd_path, char **args)
{
	if (access(node->value, X_OK) == 0)
		*cmd_path = ft_strdup(node->value);
	else
		*cmd_path = find_executable(node->value, envp);
	if (!*cmd_path)
	{
		free_args(args);
		handle_error("Command not found");
	}
}

static void execute_command(t_ast_node *node, t_data *data)
{
	pid_t pid;
	char *cmd_path;
	char **args;

	if (!node || !node->value)
		handle_error("Invalid command structure");
	args = prepare_args(node);
	pid = fork();
	if (pid == -1)
		handle_error("fork");
	if (pid == 0)
	{
		cmd_path = NULL;
		get_cmd_path(node, data->envp, &cmd_path, args);
		execve(cmd_path, args, data->envp);
		perror("execve");
		cleanup_and_exit(node, data->envp, args, cmd_path, 1);
	}
	else
	{
		free_args(args);
		waitpid(pid, NULL, 0);
	}
}

// Function to execute a pipe
static void	execute_child(t_ast_node *node, t_data *data, int *pipe_fds)
{
	close(pipe_fds[0]);
	dup2(pipe_fds[1], STDOUT_FILENO);
	close(pipe_fds[1]);
	exec_ast(node->left, data);
	exit(1);
}

// Function to execute a pipe
static void execute_pipe(t_ast_node *node, t_data *data)
{
    int pipe_fds[2];
    pid_t pid;

    if (!node || !node->left || !node->right)
    {
        write(2, "Invalid pipe structure\n", 23);
        cleanup_and_exit(node, data->envp, NULL, NULL, 1);
    }
    if (pipe(pipe_fds) == -1)
        handle_error("pipe");
    pid = fork();
    if (pid == -1)
        handle_error("fork");
    if (pid == 0)
    {
        execute_child(node, data, pipe_fds);
        cleanup_and_exit(node, data->envp, NULL, NULL, 1);
    }
    close(pipe_fds[1]);
    dup2(pipe_fds[0], STDIN_FILENO);
    close(pipe_fds[0]);
    waitpid(pid, NULL, 0);
    exec_ast(node->right, data);
}

// Function to redirect output
void	redirect_output(t_ast_node * node, int fd)
{
	if (node->type == REDIRECT_INPUT || node->type == HEREDOC)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

// Function to execute the abstract syntax tree
void	exec_ast(t_ast_node *node, t_data *data)
{
	if (!node || !data->envp)
		return ;
	if (node->type == PIPE)
		execute_pipe(node, data);
	else if (node->type == TRUNCATE || node->type == APPEND
			 || node->type == REDIRECT_INPUT || node->type == HEREDOC)
	{
		handle_redirection(node);
		exec_ast(node->left, data);
	}
	else if (!is_builtin(node))
		execute_command(node, data);
	else
		exec_builtin(node, data);
}

// Function to handle cleanup and exit
void	cleanup_and_exit(t_ast_node *root, char **envp, char **args, char *cmd_path, int status)
{
	if (root)
		free_ast(root);
	if (envp)
		free_args(envp);
	if (args)
		free_args(args);
	if (cmd_path)
		free(cmd_path);
	exit(status);
}

//
// memory leak - rendr le code lisible
// unlink le fichier tmp
//