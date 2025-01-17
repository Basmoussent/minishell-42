/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:04:24 by akassous          #+#    #+#             */
/*   Updated: 2025/01/17 18:40:17 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_token_end(char *start)
{
	char	*end;

	if (*start == '"')
		end = get_next_quote(start + 1, 1);
	else if (*start == '\'')
		end = get_next_quote(start + 1, 0);
	else
	{
		end = start;
		while (*end && !is_space(*end) && *end != '"' && *end != '\'')
			end++;
	}
	return (end);
}

char	**allocate_tokens(char *input)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

void	skip_whitespace(char **start)
{
	while (is_space(**start))
		(*start)++;
}

char	**split_whitespace(char *input)
{
	char	**tokens;
	char	*start;
	char	*end;
	int		i;

	tokens = allocate_tokens(input);
	start = input;
	i = 0;
	if (!tokens)
		return (NULL);
	while (*start)
	{
		skip_whitespace(&start);
		if (*start == '\0')
			break ;
		end = find_token_end(start);
		tokens[i++] = ft_strndup(start, end - start);
		if (!tokens[i - 1])
			return (free_tokens(tokens));
		start = is_quote(end);
	}
	tokens[i] = NULL;
	return (tokens);
}
