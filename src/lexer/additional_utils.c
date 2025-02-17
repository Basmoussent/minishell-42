/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 10:57:43 by akassous          #+#    #+#             */
/*   Updated: 2025/02/17 11:13:38 by akassous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**allocate_tokens(char *input)
{
	char	**tokens;

	tokens = ft_calloc(sizeof(char *), (count_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	skip_whitespace(char **start)
{
	while (is_space(**start))
		(*start)++;
}

int	is_special_char(char *input)
{
	return (*input == '|' || *input == '<' || *input == '>'
		|| (*input == '>' && *(input + 1) == '>')
		|| (*input == '<' && *(input + 1) == '<'));
}

char	*find_token_end(char *start)
{
	while (*start && !is_space(*start) && !is_special_char(start))
		start++;
	return (start);
}
