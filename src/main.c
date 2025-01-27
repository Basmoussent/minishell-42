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

void disable_terminal_echo()
{
    struct termios term;

	tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~ECHOCTL;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

char *read_input()
{
	char *input;

	input = readline(COLOR_CYAN_BOLD "Minishell> " COLOR_RESET);
	if (!input)
	{
		printf(COLOR_RED "exit\n" COLOR_RESET);
		return (NULL);
	}
	printf(COLOR_RESET);
	return input;
}

void	sigintHandler(int signum)
{
	(void)	signum;

	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void	sigquitHandler(int signum)
{
	(void)	signum;
}
// AFIX PSK C PAS NORMAL QUE CA FASSE QQCHOSE

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
	disable_terminal_echo();
	signal(SIGINT, sigintHandler);
	signal(SIGQUIT, sigquitHandler);
	while (1)
	{
		input = read_input();
		add_history(input);
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
