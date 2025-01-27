/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 20:21:27 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/27 19:08:13 by akassous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile int signal_received;

int heredoc_logic(char *delimiter)
{
    int fd;
    char *line;

    fd = open(HERE_DOC_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1)
    {
        perror("Error creating temporary file for heredoc");
        exit(1);
    }
    while (1)
    {
        write(1, "> ", 2);
        line = get_next_line(STDIN_FILENO);
        if (!line) // quand ya ctrl d mais ya error
        {
            printf("\n");
            break;
        }
        if (signal_received) // quand ya ctrl c mais ya error
        {
            free(line);
            close(fd);
            return (open(HERE_DOC_TMP, O_WRONLY | O_CREAT | O_TRUNC, 0644));
        }
        if (strncmp(line, delimiter, strlen(delimiter)) == 0 && line[strlen(delimiter)] == '\n')
        {
            free(line);
            break;
        }
        write(fd, line, strlen(line));
        free(line);
    }
    close(fd);
    return (open(HERE_DOC_TMP, O_RDONLY));
}
