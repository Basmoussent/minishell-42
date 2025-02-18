/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:26:05 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/18 12:21:47 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_loop(t_data *data)
{
	while (1)
	{
		data->hd_file = ft_strdup("");
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		data->input = read_input();
		if (!data->input)
			break ;
		add_history(data->input);
		process_input(data);
		cleanup_current_iteration(data);
	}
}
