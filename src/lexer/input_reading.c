/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:04:24 by akassous          #+#    #+#             */
/*   Updated: 2025/01/17 17:54:44 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t ft_strnlen(const char *s, size_t maxlen)
{
    size_t len = 0;
    while (len < maxlen && s[len] != '\0')
    {
        len++;
    }
    return len;
}

static char *ft_strndup(const char *s, size_t n)
{
    char *dup;
    size_t len = ft_strnlen(s, n);

    dup = (char *)malloc(len + 1);
    if (!dup)
        return NULL;

    ft_strlcpy(dup, s, len + 1);
    return dup;
}

static char *find_token_end(char *start)
{
    char *end;

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
    return end;
}

char **allocate_tokens(char *input)
{
    char **tokens = malloc(sizeof(char *) * (count_tokens(input) + 1));
    if (!tokens)
        return NULL;
    return tokens;
}

void skip_whitespace(char **start)
{
    while (is_space(**start))
        (*start)++;
}

char **split_whitespace(char *input)
{
    char **tokens = allocate_tokens(input);
    char *start = input;
    char *end;
    int i = 0;

    if (!tokens)
        return NULL;

    while (*start)
    {
        skip_whitespace(&start);
        if (*start == '\0')
            break;
        end = find_token_end(start);
        tokens[i++] = ft_strndup(start, end - start);
        if (!tokens[i - 1])
        {
            free(tokens);
            return NULL;
        }
        start = (*end == '"' || *end == '\'') ? end + 1 : end;
    }
    tokens[i] = NULL;
    return tokens;
}
