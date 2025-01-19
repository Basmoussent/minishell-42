/* ************************************************************************** */
/*      */
/*    ::: ::::::::   */
/*   echo.c   :+:   :+: :+:   */
/*    +:+ +:+ +:+   */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+  */
/*    +#+#+#+#+#+   +#+  */
/*   Created: 2025/01/03 14:56:20 by bdenfir           #+#  #+# */
/*   Updated: 2025/01/14 19:18:33 by bdenfir          ###   ########.fr */
/*      */
/* ************************************************************************** */

#include "minishell.h"

// Function to skip spaces in the input
char    *ft_skip_spaces(char *input)
{
    while (*input == ' ')
        input++;
    return input;
}

//Function to check if the -n flag is present
bool	ft_check_n_flag(char **input)
{
	bool	n_flag;

	n_flag = false;
	while (strncmp(*input, "-n", 2) == 0 && ((*input)[2] == '\0'
        || (*input)[2] == ' '))
	{
		n_flag = true;
		*input = ft_skip_spaces(*input + 2);
	}
	return (n_flag);
}

// Function to process the input and remove quotes
void	ft_process_input(char *input, char *buffer)
{
	bool	in_single_quotes;
	bool	in_double_quotes;
	int		i;
	int		buffer_index;

	in_single_quotes = false;
	in_double_quotes = false;
	buffer_index = 0;
	i = -1;
	while (input[++i] != '\0')
	{
		if (input[i] == '\'' && !in_double_quotes)
		{	
            in_single_quotes = !in_single_quotes;
			continue ;
		}
        if (input[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			continue ;
		}
		buffer[buffer_index++] = input[i];
	}
	buffer[buffer_index] = '\0';
}

//Main function to implement the echo command
int	ft_echo(char *input)
{
	char	buffer[20000];
	bool	n_flag;

	if (!validate_command(input))
		return (KO);
	if (!input)
		return (printf("\n"));
	if (strncmp(input, "echo", 4) == 0 && (input[4] == ' ' || input[4] == '\0'))
		input = ft_skip_spaces(input + 4);
	input = ft_skip_spaces(input);
	n_flag = ft_check_n_flag(&input);
	ft_process_input(input, buffer);
	if (!n_flag)
		printf("%s\n", buffer);
	else
		printf("%s", buffer);
	return (OK);
}
