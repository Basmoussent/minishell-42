/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:27 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/20 20:24:53 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_logic(char *delimiter)
{
	int		fd;
	char	*line;
	char	*tempfile = ".heredoc_tmp";

	fd = open(tempfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("Error creating temporary file for heredoc");
		exit(1);
	}
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\n')
		{
			free(line);
			break;
		}
		write(fd, line, strlen(line));
		free(line);
	}
	close(fd);
	fd = open(tempfile, O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening temporary file for heredoc");
		exit(1);
	}
	unlink(tempfile);
	return (fd);
}
