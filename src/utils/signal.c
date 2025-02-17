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
	}
}
