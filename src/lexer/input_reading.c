/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:04:24 by akassous          #+#    #+#             */
/*   Updated: 2025/02/11 22:42:28 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_char(char *input)
{
	return (*input == '|' || *input == '<' || *input == '>'
		|| (*input == '>' && *(input + 1) == '>')
		|| (*input == '<' && *(input + 1) == '<'));
}

static char	*find_token_end(char *start)
{
	while (*start && !is_space(*start) && !is_special_char(start))
		start++;
	return (start);
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

char **split_whitespace(char *input) {
    char 	**tokens;
    char 	*start;
    char 	*end;
    int		i;

	i = 0;
    tokens = allocate_tokens(input);
    if (!tokens)
        return (NULL);
    start = input;
    while (*start)
	{
        skip_whitespace(&start);
        if (*start == '\0')
            break ;
        if (is_special_char(start))
		{
            end = start + 1;
            if (*start == '>' && *(start + 1) == '>')
                end = start + 2;
			else if (*start == '<' && *(start + 1) == '<')
                end = start + 2;
            tokens[i++] = ft_strndup(start, end - start);
            if (!tokens[i - 1])
                return (free_tokens(tokens));
            start = end;
        }
        else if (*start == '"' || *start == '\'')
            start = is_quote(start);
		else 
		{
            end = find_token_end(start);
            tokens[i++] = ft_strndup(start, end - start);
            if (!tokens[i - 1])
                return free_tokens(tokens);
            start = end;
        }
    }
    tokens[i] = NULL;
    return (tokens);
}
