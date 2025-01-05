/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:09:22 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/03 16:14:56 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **envp)
{
	int	i;

	if (!envp || !*envp)
		return (KO);
	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PWD", 3) == 0)
		i++;
	printf("%s\n", ft_strchr(envp[i], '/'));
	return (OK);
}

