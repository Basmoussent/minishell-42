/* ************************************************************************** */
/*									  */
/*							:::	 ::::::::   */
/*   exit.c			:+:   :+:	:+:   */
/*						  +:+ +:+	   +:+	*/
/*   By: bdenfir <bdenfir@42.fr>					+#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	 */
/*   Created: 2025/01/14 22:37:39 by bdenfir		   #+#  #+#		  */
/*   Updated: 2025/01/14 22:44:57 by bdenfir		  ###   ########.fr	*/
/*									  */
/* ************************************************************************** */

#include "minishell.h"

static int is_number(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static void print_error(char *msg, char *arg)
{
	write(STDERR_FILENO, "exit\n", 5);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (arg)
	{
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, ": ", 2);
	}
	write(STDERR_FILENO, "\n", 1);
}

int	is_within_long_long_range(const char *str)
{
	int		len;
	const char	*limit;

	limit = "9223372036854775807";
	if (str[0] == '-')
		limit ="9223372036854775808";
	str = str +(str[0] == '-');
	len = 0;
	while (str[len])
		len++;
	if (len > 19)
		return (0);
	if (len < 19)
		return (1);
	while (*str++ && *limit++)
	{
		if (*str > *limit)
			return (0);
		if (*str < *limit)
			return (1);
	}
	return (1);
}


static int handle_exit_error(char *arg)
{
	if (!is_within_long_long_range(arg) || !is_number(arg))
	{
		print_error("minishell: exit: ", arg);
		print_error("numeric argument required", NULL);
		return (2);
	}
	return (0);
}

int ft_exit(char *input)
{
	char		*arg;
	long long   exit_status;

	arg = input;
	exit_status = 0;
	if (*arg == '\0')
		exit(0);
	if (ft_strchr(arg, ' '))
	{
		print_error("minishell: exit: too many arguments", NULL);
		return (1);
	}
	if (handle_exit_error(arg))
		return (2);
	if (*arg)
	{
		exit_status = ft_atol(arg);
		if (exit_status < 0)
			exit_status = 256 + exit_status % 256;
		write(STDERR_FILENO, "exit\n", 5);
		exit(exit_status);
	}
	return (exit_status);
}
