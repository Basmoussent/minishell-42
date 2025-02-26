/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:04:24 by akassous          #+#    #+#             */
/*   Updated: 2025/02/26 15:17:40 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_special_char(char *start, char **tokens, int *i)
{
	char	*end;

	end = start + 1;
	if ((*start == '>' && *(start + 1) == '>')
		|| (*start == '<' && *(start + 1) == '<'))
		end = start + 2;
	tokens[*i] = ft_strndup(start, end - start);
	if (!tokens[*i])
		return (NULL);
	(*i)++;
	return (end);
}

char	*handle_quotes(char *start, char **tokens, int *i)
{
    char	*end;
    
    while (*start && (*start == '"' || *start == '\'') && *(start + 1) == *start)
        start += 2;
    if (*start && *start != '"' && *start != '\'')
    {
        end = find_token_end(start);
        tokens[*i] = ft_strndup(start, end - start);
        if (!tokens[*i])
            return (NULL);
        (*i)++;
        return (end);
    }
    if (*start == '"' || *start == '\'')
    {
        end = get_next_quote(start + 1, *start == '"');
        if (*end == *start)
            end++;
        tokens[*i] = ft_strndup(start, end - start);
        if (!tokens[*i])
            return (NULL);
        (*i)++;
        return (end);
    }
    return (start);
}

char	*handle_token(char *start, char **tokens, int *i)
{
	char	*end;

	end = find_token_end(start);
	tokens[*i] = ft_strndup(start, end - start);
	if (!tokens[*i])
		return (NULL);
	(*i)++;
	return (end);
}

char	*process_token(char *start, char **tokens, int *i)
{
	if (is_special_char(start))
		return (handle_special_char(start, tokens, i));
	else if (*start == '"' || *start == '\'')
		return (handle_quotes(start, tokens, i));
	else
		return (handle_token(start, tokens, i));
}

char	**split_whitespace(char *input)
{
	char	**tokens;
	char	*start;
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
		start = process_token(start, tokens, &i);
		if (!start)
		{
			free_args(tokens);
			return (NULL);
		}
	}
	tokens[i] = NULL;
	return (tokens);
}
