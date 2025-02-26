/* ************************************************************************** */
/*	  */
/*	::: ::::::::   */
/*   echo.c   :+:   :+: :+:   */
/*	+:+ +:+ +:+   */
/*   By: bdenfir <bdenfir@42.fr>					+#+  +:+	   +#+  */
/*	+#+#+#+#+#+   +#+  */
/*   Created: 2025/01/03 14:56:20 by bdenfir		   #+#  #+# */
/*   Updated: 2025/01/14 19:18:33 by bdenfir		  ###   ########.fr */
/*	  */
/* ************************************************************************** */

#include "minishell.h"

// Function to skip spaces in the input
char	*ft_skip_spaces(char *input)
{
	while (*input == ' ' || *input == '\t' || *input == '\n' || *input == '\r' || *input == '\v' || *input == '\f')
		input++;
	return (input);
}

// Function to check if the -n flag is present
bool    ft_check_n_flag(char **input)
{
    bool    n_flag;
    char    *temp;
    char    quote_char;

    n_flag = false;
    while (**input == '-' || **input == '\"' || **input == '\'')
    {
        quote_char = 0;
        if (**input == '\"' || **input == '\'')
        {
            quote_char = **input;
            (*input)++;
            if (**input != '-')
                break ;
        }
        temp = *input + 1;
        while (*temp == 'n')
            temp++;
        if (*temp != ' ' && *temp != '\0' && *temp != quote_char)
            break;
        if (quote_char && *temp == quote_char)
            temp++;
        n_flag = true;
        *input = ft_skip_spaces(temp);
    }
    return (n_flag);
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
	input = ft_skip_spaces(input);
	n_flag = ft_check_n_flag(&input);
	ft_process_input(input, buffer);
	if (!n_flag)
		printf("%s\n", buffer);
	else
		printf("%s", buffer);
	return (OK);
}
