/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:17:30 by akassous          #+#    #+#             */
/*   Updated: 2025/02/16 23:37:42 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quote(char *token)
{
	char	quote_char;

	quote_char = '\0';
	while (*token)
	{
		if (*token == '\'' || *token == '"')
		{
			if (quote_char == '\0')
				quote_char = *token;
			else if (quote_char == *token)
				quote_char = '\0';
		}
		token++;
	}
	if (quote_char != '\0')
	{
		ft_putstr_fd("minishell: unclosed quote\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

char	*get_last_token(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i + 1])
		i++;
	return (tokens[i]);
}

t_ast_node	*double_free_input(char	**args)
{
    int i;

    if (!args)
        return (NULL);
    i = 0;
    while (args[i])
    {
        ft_free((void **)&args[i]);
        i++;
    }
    ft_free((void **)&args);
	args = NULL;
	return (NULL);
}

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
	if (!true_input || has_unclosed_quote(get_last_token(true_input)))
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
