/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:26:05 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/17 21:14:20 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_shell(t_data *data)
{
	if (!data)
		return ;
	if (data->current_ast)
	{
		free_ast(data->current_ast);
		data->current_ast = NULL;
	}
	if (data->tokens)
	{
		free_args(data->tokens);
		data->tokens = NULL;
	}
	if (data->saved_stdin != -1)
	{
		close(data->saved_stdin);
		data->saved_stdin = -1;
	}
	if (data->saved_stdout != -1)
	{
		close(data->saved_stdout);
		data->saved_stdout = -1;
	}
	cleanup_data_strings(data);
	cleanup_data_arrays(data);
	clear_history();
}

void	cleanup_data_strings(t_data *data)
{
	if (data->input)
	{
		ft_free((void **)&data->input);
		data->input = NULL;
	}
	if (data->hd_file)
	{
		unlink(data->hd_file);
		ft_free((void **)&data->hd_file);
		data->hd_file = NULL;
	}
}

void	cleanup_data_arrays(t_data *data)
{
	if (data->envp)
	{
		free_args(data->envp);
		data->envp = NULL;
	}
	if (data->export)
	{
		free_args(data->export);
		data->export = NULL;
	}
}
