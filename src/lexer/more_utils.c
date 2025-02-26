/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:44:55 by amine             #+#    #+#             */
/*   Updated: 2025/02/26 23:44:36 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		found_builtin(char *input)
{
	return (input[0] == '|' || input[0] == '>' || input[0] == '<');
}

static char	**temp_loop(char **tokens, char **fix_tokens)
{
	int		i;

	i = 0;
    while (tokens[i])
    {
        if (tokens[i] && tokens[i + 1] && tokens[i + 2] && 
			is_speci(tokens[i]) && !is_speci(tokens[i + 1])
			&& !is_speci(tokens[i + 2]))
		{
			fix_tokens[i] = ft_strdup(tokens[i + 2]);
			fix_tokens[i + 1] = ft_strdup(tokens[i]);
			fix_tokens[i + 2] = ft_strdup(tokens[i + 1]);
			if (!fix_tokens[i] || !fix_tokens[i + 1] || !fix_tokens[i + 2])
				return (NULL);
			i += 3;
		}
		else
		{
			fix_tokens[i] = ft_strdup(tokens[i]);
			if (!fix_tokens[i])
				return (NULL);
			i++;
		}
    }
	return (fix_tokens);
}

char	**fix_order(char **tokens)
{
    char	**fixed_tokens;
	int		count;

	count = count_tokens_array(tokens);
    fixed_tokens = malloc(sizeof(char *) * (count_tokens_array(tokens) + 1));
    if (!fixed_tokens)
	{
        return (NULL);
	}
	fixed_tokens = temp_loop(tokens, fixed_tokens);
	if (!fixed_tokens)
		return (NULL);
    fixed_tokens[count] = NULL;
    return (fixed_tokens);
}