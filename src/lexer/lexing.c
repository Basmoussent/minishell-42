/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:17:30 by akassous          #+#    #+#             */
/*   Updated: 2025/01/17 17:17:03 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// enum s_token lexer(char *input)
// {
// 	if (*input == "|")
// 		return PIPE;
// 	if (*input == ">")
// 		return TRUNCATE;
// 	if (*input == ">>")
// 		return APPEND;
// 	if (*input == "<")
// 		return REDIRECT_INPUT;
// 	if (*input == "<<")
// 		return HEREDOC;
//     return NONE;
// }

char    *lexing(char *input)
{
    int		count;
    char	**lexed_input;

	input = trim_input(input);
    count = count_tokens(input);
    if (!count)
        return (NULL);
    lexed_input = split_whitespace(input);
}
