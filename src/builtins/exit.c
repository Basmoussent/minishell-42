/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 22:37:39 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/14 22:44:57 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int is_number(char *str)
{
    if (*str == '-' || *str == '+')
        str++;
    if (*str == '\0')
        return (0);
    while (*str)
    {
        if (!ft_isdigit(*str))
            return (0);
        str++;
    }
    return (1);
}

static void print_error(char *msg, char *arg)
{
    write(STDERR_FILENO, "exit\n", 5);
    write(STDERR_FILENO, msg, ft_strlen(msg));
    if (arg)
    {
        write(STDERR_FILENO, arg, ft_strlen(arg));
        write(STDERR_FILENO, ": ", 2);
    }
    write(STDERR_FILENO, "\n", 1);
}

int ft_exit(char *input)
{
    char    *arg;
    int     exit_status;
    char    *next_space;

    exit_status = 0;
    arg = input + 4;
    while (*arg == ' ')
        arg++;

    next_space = ft_strchr(arg, ' ');
    if (next_space)
    {
        print_error("minishell: exit: too many arguments", NULL);
        return (1);
    }
    if (*arg)
    {
        if (is_number(arg))
        {
            exit_status = atoi(arg);
            if (exit_status < 0)
                exit_status = -exit_status;
        }
        else
        {
            print_error("minishell: exit: ", arg);
            print_error("numeric argument required", NULL);
            return (2);
        }
    }
    write(STDERR_FILENO, "exit\n", 5);
    exit(exit_status);
    return (exit_status);
}
