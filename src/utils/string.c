/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 19:53:57 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/19 19:54:03 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	validate_command(const char *cmd)
{
	bool	in_single_quote;
	bool	in_double_quote;

	in_single_quote = false;
	in_double_quote = false;
	if (!cmd)
		return (false);
	while (*cmd)
	{
		if (*cmd == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (*cmd == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		else if (!in_single_quote && !in_double_quote && (*cmd == ';' || 
			*cmd == '&' || *cmd == '|' || *cmd == '<' || *cmd == '>'))
			return (false);
		cmd++;
	}
	return (!in_single_quote && !in_double_quote);
}