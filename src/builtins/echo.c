/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:56:20 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/14 19:18:33 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(char *str)
{
    char	*params;
    int		newline;

    params = ft_skipt_it(str, ' ');
    newline = 1;
    while (params && ft_strncmp(params, "-n", 2) == 0 && (params[2] == ' ' || params[2] == '\0'))
    {
        newline = 0;
        params = ft_skipt_it(params + 2, ' ');
    }
    handle_echo(params, newline);
    return (OK);
}

int	handle_echo(char *params, int newline)
{
    if (params)
        printf("%s", params);
    if (newline)
        printf("\n");
    return (OK);
}