/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_and_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 14:35:30 by amine             #+#    #+#             */
/*   Updated: 2025/01/17 18:36:58 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_next_quote(char *input, int double_qte)
{
	char	sep;
	int		i;

	i = 0;
	if (!double_qte)
		sep = '\'';
	else
		sep = '"';
	while (*input && *input != sep)
		*input++;
	return (input);
}

int	count_tokens(char *input)
{
	char	*start;
	int		token_count;

	start = input;
	token_count = 0;
	while (*start)
	{
		while (is_space(*start))
			start++;
		if (*start == '\0')
			break ;
		token_count++;
		if (*start == '\'')
			start = get_next_quote(start, 1);
		else if (*start == '"')
			start = get_next_quote(start, 0);
		else
		{
			while (*start && !is_space(*start))
				start++;
		}
	}
	return (token_count);
}

char	*trim_input(char *input)
{
	char	*end;

	while (is_space((unsigned char)*input))
		input++;
	if (*input == 0)
		return (input);
	end = input + ft_strlen(input) - 1;
	while (end > input && is_space((unsigned char)*end))
		end--;
	*(end + 1) = '\0';
	return (input);
}
