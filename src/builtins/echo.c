/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:56:20 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/03 16:01:16 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_echo(char *str)
{
	char	*params;

	params = ft_skipt_it(str, ' ');
	if (params && ft_strncmp(params, "-n ", 3) == 0)
		echo(str, params);
	else
		echo(str, NULL);
	return (OK);
}

int echo(char *str, char *params)
{	
	if (!params)
		printf("%s\n", ft_skipt_it(str, ' '));
	else
		printf("%s", ft_skipt_it(params, ' '));
	return (OK);
	
}