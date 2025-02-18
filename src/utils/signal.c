/* ************************************************************************** */
/*									  */
/*							:::	 ::::::::   */
/*   signal.c								 :+:   :+:	:+:   */
/*						  +:+ +:+	   +:+	*/
/*   By: bdenfir <bdenfir@42.fr>					+#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	 */
/*   Created: 2025/01/27 16:25:11 by akassous		#+#  #+#		  */
/*   Updated: 2025/01/29 15:26:41 by bdenfir		  ###   ########.fr	*/
/*									  */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
        g_signal_received = 130;
	}
	else if (signum == SIGQUIT)
		signal(SIGQUIT, SIG_IGN);
}

void sigquit_handler(int signum)
{
    (void)signum;
    write(1, "Quit (core dumped)\n", 19);
	g_signal_received = 131;
    signal(SIGQUIT, SIG_DFL);
    kill(getpid(), SIGQUIT);
}

void	handle_signals_child(void)
{
	struct sigaction sa;

	sa.sa_handler = SIG_DFL;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}
