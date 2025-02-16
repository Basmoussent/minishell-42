/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:17:30 by akassous          #+#    #+#             */
/*   Updated: 2025/02/10 16:10:05 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast_node	*lexing(char *input, t_data *data)
{
	char		**lexed_input;
	char		**true_input;
	t_ast_node	*ast;

	input = trim_input(input);
	if (!count_tokens(input))
		return (NULL);
	lexed_input = split_whitespace(input);
	if (!lexed_input)
		return (NULL);
	true_input = filter_tokens(lexed_input);
	if (!true_input)
	{
		free_args(lexed_input);
		return (NULL);
	}
	ast = parse_tokens(true_input, data);
	free_args(true_input);
	if (!ast)
	{
		free_args(lexed_input);
		return (NULL);
	}
	data->tokens = lexed_input;
	return (ast);
}
