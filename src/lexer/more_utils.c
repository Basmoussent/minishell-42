/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:44:55 by amine             #+#    #+#             */
/*   Updated: 2025/02/26 22:57:25 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		found_builtin(char *input)
{
	return (input[0] == '|' || input[0] == '>' || input[0] == '<');
}

char	**fix_order(char **tokens)
{
    int		i;
    char	**fixed_tokens;

    fixed_tokens = malloc(sizeof(char *) * (count_tokens_array(tokens) + 1));
    if (!fixed_tokens)
        return (NULL);
    i = 0;
    while (tokens[i])
    {
        if (is_speci(tokens[i]) && !is_speci(tokens[i + 1])
			&& !is_speci(tokens[i + 2]))
		{
			fixed_tokens[i + 1] = ft_strdup(tokens[i]);
			fixed_tokens[i] = ft_strdup(tokens[i + 2]);
			fixed_tokens[i + 2] = ft_strdup(tokens[i + 1]);
			i += 3;
		}
		else
		{
			fixed_tokens[i] = ft_strdup(tokens[i]);
			i++;
		}
    }
    fixed_tokens[i] = NULL;
	printf("%s %s %s\n", fixed_tokens[0], fixed_tokens[1], fixed_tokens[2]);
    return (fixed_tokens);
}