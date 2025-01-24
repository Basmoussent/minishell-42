/* ************************************************************************** */
/*									  */
/*							:::	 ::::::::   */
/*   main.c			:+:   :+:	:+:   */
/*						  +:+ +:+	   +:+	*/
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	 */
/*   Created: 2025/01/20 17:26:05 by bdenfir		   #+#  #+#		  */
/*   Updated: 2025/01/22 20:39:10 by bdenfir		  ###   ########.fr	*/
/*									  */
/* ************************************************************************** */

#include "minishell.h"

char *read_input()
{
	char *input;

	input = readline(COLOR_CYAN_BOLD "Minishell> " COLOR_RESET);
	if (!input)
	{
		// Exit gracefully without printing error for EOF
		printf(COLOR_RED "exit\n" COLOR_RESET);
		exit(EXIT_SUCCESS);
	}
	printf(COLOR_RESET);
	return input;
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
	data.ast = 1;
	while (1)
	{
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
			if (data.ast)
				print_ast(ast, "", 0);
			exec_ast(ast, &data);
			free_ast(ast);
		}
		free_tokens(tokens);
		free(input);
	}
	free_args(data.envp);
	return 0;
}
