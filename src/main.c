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

#include "../include/minishell.h"
#include <readline/readline.h>


volatile int signal_received = 0;

char *read_input()
{
    char *input;
    
    input = readline(COLOR_CYAN_BOLD "Minishell> " COLOR_RESET);
    if (!input)
    {
        printf(COLOR_RED "exit\n" COLOR_RESET);
        exit(EXIT_SUCCESS);
    }
    return input;
}

int main(int argc, char **argv, char **envp)
{
    t_data data;
    char *input;
    t_ast_node *ast;

    if (argc != 1 || !argv[0])
        return (0);
    data.envp = copy_envp(envp);
    data.ast = 1;
    while (1)
    {
        data.hd_file = ft_strdup("");
        unlink(data.hd_file);
        free(data.hd_file);
        signal(SIGINT, handle_signals);
    	signal(SIGQUIT, SIG_IGN);
        input = read_input();
        add_history(input);
        ast = lexing(input, &data);
        if (ast)
        {
            if (data.ast)
                print_ast(ast, "", 0);
            exec_ast(ast, &data);
            free_ast(ast);
        }
    }
    free_args(data.envp);
    return 0;
}
