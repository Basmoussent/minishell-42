/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:27 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/29 15:23:22 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int signal_received;

char	*generate_unique_filename(void)
{
	int		count;
	char	*num;
	char	*filename;
	char	*tmp;

	count = 1;
	filename = ft_strdup(HERE_DOC_TMP);
	while (access(filename, F_OK) == 0)
	{
		num = ft_itoa(count++);
		tmp = filename;
		filename = ft_strjoin(HERE_DOC_TMP, "_");
		free(tmp);
		tmp = filename;
		filename = ft_strjoin(tmp, num);
		free(tmp);
		free(num);
	}
	return (filename);
}

int	heredoc_logic(char *delimiter, t_data *data)
{
	int		fd;
	char	*line;

	data->hd_file = generate_unique_filename();
	fd = open(data->hd_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror("open"), free(data->hd_file), -1);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strnstr(line, delimiter, ft_strlen(line)) != NULL)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	fd = open(data->hd_file, O_RDONLY);
	return (fd);
}
