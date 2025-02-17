/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:52:45 by akassous          #+#    #+#             */
/*   Updated: 2025/02/17 16:55:47 by akassous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *input)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*result;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
    while (input[i])
    {
		if (input[i] == '\'' || input[i] == '"')
		{
			i++;
			continue ;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}
