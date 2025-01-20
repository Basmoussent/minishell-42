/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:26:05 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/20 23:05:05 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	t_data data;
	data.envp = copy_envp(envp);
	char **tokens = split_whitespace(argv[argc-1]);
	t_ast_node *ast = parse_tokens(tokens, &data);
	print_ast(ast, "", 0);
	exec_ast(ast, data.envp);	
	free(tokens);
	free_ast(ast);
	free_args(data.envp);
	
}