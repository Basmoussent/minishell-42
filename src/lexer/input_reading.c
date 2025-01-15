/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_reading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:04:24 by akassous          #+#    #+#             */
/*   Updated: 2025/01/14 22:10:31 by akassous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int is_space(char c)
// {
// 	return (c == ' ' || c == '\t' || c == '\n' 
// 		|| c == '\r' || c == '\f' || c == '\v');
// }

// char	*get_next_quote(char *input, int double_qte)
// {
// 	char	sep;
// 	int		i;
	
// 	i = 0;
// 	if (!double_qte)
// 		sep = '\'';
// 	else sep = '"';
// 	while (*input && *input != sep)
// 		*input++;
// 	return (input);	
// }

// int	count_tokens(char *input)
// {
//     char	*start;
//     int		token_count;

// 	start = input;
// 	token_count = 0;
//     while (*start)
// 	{
//         while (is_space(*start))
//             start++;
//         if (*start == '\0')
//             break;
//         token_count++;
// 		if (*start == "\'")
// 			start = get_next_quote(start, 1);
// 		else if (*start == '"')
// 			start = get_next_quote(start, 0);
//         else while (*start && !is_space(*start))
//             start++;
// 	}
//     return (token_count);
// }

// char	*split_whitespace(char *input)
// {
// 	char	*start;
// 	char	*end;
// 	char	*tokens;
// 	int		token_count;

// 	tokens = malloc(sizeof(char) * count_tokens(input));
// 	if (!tokens)
// 		return (0);
// 	while (*start)
// 	{
// 		while (is_space(*start))
// 			start++;
// 		if (!start)
// 			break;
// 		if (*start == '"')
// 			end = get_next_quote(start, 1);
// 		else if (*start == '\'')
// 			end = get_next_quote;
// 		else
// 		{
// 			end = start;
// 			while (*end != '\0' && is_space(*end))
// 				end++;
// 			tokens[token_count] = malloc (*end - *start + 1);
// 			if (!tokens[token_count])
// 				return (0);
// 			//strncpy(tokens[*token_count], start, length);
// 			tokens[token_count][*end - *start] = '\0';
// 			(token_count)++;
// 			start = end;
// 		}
// 	}
// 	return (tokens);
// }

// char	*trim_input(char *input)
// {
// 	char	*end;
	
// 	while (is_space((unsigned char)*input))
// 		input++;
// 	if (*input == 0)
// 		return (input);
// 	end = input + ft_strlen(input) - 1;
// 	while (end > input && is_space((unsigned char)*end))
// 		end--;
// 	*(end + 1) = '\0';
// 	return (input);
// }
