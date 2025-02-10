/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:04:11 by amine             #+#    #+#             */
/*   Updated: 2025/02/10 16:11:58 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_speci(char *token)
{
    return (token[0] == '>');
}

int count_tokens_array(char **tokens)
{
    int count = 0;
    while (tokens[count])
        count++;
    return count;
}

char **filter_tokens(char **tokens)
{
    char **filtered_tokens;
    int i, j;
    char *last_redirection = NULL;
    char *last_target = NULL;

    filtered_tokens = malloc(sizeof(char *) * (count_tokens_array(tokens) + 1));
    if (!filtered_tokens)
        return NULL;
    i = 0;
    j = 0;
    while (tokens[i])
    {
        if (is_speci(tokens[i]))
        {
            last_redirection = tokens[i];
            if (tokens[i + 1])
                last_target = tokens[i + 1];
            i += 2;
        }
        else
            filtered_tokens[j++] = tokens[i++];
    }
    if (last_redirection && last_target)
    {
        filtered_tokens[j++] = last_redirection;
        filtered_tokens[j++] = last_target;
    }
    filtered_tokens[j] = NULL;
    return (filtered_tokens);
}

// Rajouter une fonction qui créé les fichiers