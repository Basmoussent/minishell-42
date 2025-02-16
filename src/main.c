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

volatile int	g_signal_received = 0;

void cleanup_shell(t_data *data)
{
    if (!data)
        return;
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
    clear_history();
}

static char	*read_input(void)
{
	char	*input;

	input = readline(COLOR_CYAN_BOLD "Minishell> " COLOR_RESET);
	if (!input)
	{
		ft_putstr_fd(COLOR_RED "exit\n" COLOR_RESET, 1);
		return (NULL);
	}
	return (input);
}

static void	init_shell(t_data *data, char **envp)
{
	data->envp = copy_envp(envp);
	data->export = copy_export_list(envp);
	data->ast = 0;
	data->current_ast = NULL;
	data->tokens = NULL;
	data->input = NULL;
	data->hd_file = NULL;
	data->status = 0;
	if (!data->envp || !data->export)
	{
		cleanup_shell(data);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data		data;

	(void)argc;
	(void)argv;
	init_shell(&data, envp);
	while (1)
	{
		data.hd_file = ft_strdup("");
		signal(SIGINT, handle_signals);
		signal(SIGQUIT, SIG_IGN);
		data.input = read_input();
		if (!data.input)
			break ;
		add_history(data.input);
		if (data.current_ast)
		{
			free_ast(data.current_ast);
			data.current_ast = NULL;
		}
		data.current_ast = lexing(data.input, &data);
		if (data.current_ast)
    	    print_ast(data.current_ast, "", 0);
        if (data.current_ast)
			exec_ast(data.current_ast, &data);
		if (data.input)
		{
			free(data.input);
			data.input = NULL;
		}
		if (data.hd_file)
		{
			unlink(data.hd_file);
			free(data.hd_file);
			data.hd_file = NULL;
		}
	}
	cleanup_shell(&data);
	return (0);
}
