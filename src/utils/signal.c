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
}

void	sigquit_handler(int signum)
{
	(void)signum;
	write(2, "\nQuit (Core Dumped)\n\n", 20);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_signal_received = 131;
}

void	handle_signals_child(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigquit_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
}
