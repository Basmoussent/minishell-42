/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:26:05 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/22 02:49:47 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void prompt()
{
    printf("minishell> ");
}

char *read_input()
{
	char	*input;

	input = get_next_line(STDIN_FILENO);
	if (!input)
	{
		perror("get_next_line");
		exit(EXIT_FAILURE);
	}
	return (input);
}

int main(int argc, char **argv, char **envp)
{
    t_data		data;
	char		*input;
	t_ast_node	*ast;
	char		**tokens;

	if (argc != 1 || !argv[0])
		return (0);
    data.envp = copy_envp(envp);
    while (1)
    {
        prompt();
        input = read_input();
        if (!input)
            break ;
        tokens = split_whitespace(input);
        if (!tokens)
        {
            free(input);
            continue ;
        }
        ast = parse_tokens(tokens, &data);
        if (ast)
        {
            exec_ast(ast, data.envp);
            free_ast(ast);
        }
        free_tokens(tokens);
        free(input);
    }
    free_args(data.envp);
    return 0;
}
