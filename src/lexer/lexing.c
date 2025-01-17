/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:17:30 by akassous          #+#    #+#             */
/*   Updated: 2025/01/17 23:49:12 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*lexing(char *input)
{
	int			count;
	char		**lexed_input;
	t_ast_node	*ast;

	input = trim_input(input);
	count = count_tokens(input);
	if (!count)
		return (NULL);
	lexed_input = split_whitespace(input);
	if (!lexed_input)
		return (NULL);
	ast = parse_tokens(lexed_input);
}
