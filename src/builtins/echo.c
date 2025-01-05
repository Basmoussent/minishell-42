/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 14:56:20 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/05 20:19:56 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_echo(char *str)
{
	char	*params;

	params = ft_skipt_it(str, ' ');
	while (params && ft_strncmp(params, "-n ", 3) == 0)
		params = ft_skipt_it(params + 2, ' ');
	echo(params);
	return (OK);
}

int	echo(char *params)
{
	if (!params)
		printf("%s\n", ft_skipt_it(params, ' '));
	else
		printf("%s", params);
	return (OK);
}

