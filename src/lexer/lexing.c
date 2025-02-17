/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:17:30 by akassous          #+#    #+#             */
/*   Updated: 2025/02/17 21:26:15 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quote(char *token)
{
	int	single_quotes;
	int	double_quotes;
	
	single_quotes = 0;
	double_quotes = 0;
	while (*token)
	{
		if (*token == '\'')
			single_quotes++;
		else if (*token == '"')
			double_quotes++;
		token++;
	}
	/*if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
	{
		ft_putstr_fd("error : unclosed quote\n", STDERR_FILENO);
		return (1);
	}*/
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
	int	i;

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

int	check_doubles(char **lexed_input)
{
	int	i;

	i = 0;
	while (lexed_input[i + 1])
	{
		if (is_special_char(lexed_input[i])
			&& is_special_char(lexed_input[i + 1]))
		{
			printf("minishell: syntax error near unexpected token `newline'\n");
			g_signal_received = 2;
			return (0);
		}
		i++;
	}
	if (is_special_char(lexed_input[i]))
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		g_signal_received = 2;
		return (0);
	}
	return (1);
}
#include <stdio.h>

void print_char_array(char **arr)
{
    int i = 0;

    // Loop through the array until a NULL pointer is encountered
    while (arr[i] != NULL)
    {
        printf("%s\n", arr[i]);  // Print each string followed by a newline
        i++;
    }
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
	print_char_array(lexed_input);
	if (!lexed_input || !check_doubles(lexed_input))
		return (double_free_input(lexed_input));
	true_input = filter_tokens(lexed_input);
	if (!true_input)
	{
		return (double_free_input(lexed_input));
	}
	free_args(lexed_input);
	if (has_unclosed_quote(get_last_token(true_input)))
		return (double_free_input(true_input));
	ast = parse_tokens(true_input, data);
	free_args(true_input);
	if (!ast)
		return (double_free_input(lexed_input));
	return (ast);
}
