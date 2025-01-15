/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   echo.c            :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2025/01/03 14:56:20 by bdenfir           #+#  #+#          */
/*   Updated: 2025/01/14 19:18:33 by bdenfir          ###   ########.fr    */
/*                                      */
/* ************************************************************************** */

#include "minishell.h"

void ft_echo(char *input) {
    bool in_single_quotes = false;
    bool in_double_quotes = false;
    char buffer[20000];
    int buffer_index = 0;

    input = ft_skipt_it(input, ' ');
    for (int i = 0; input[i] != '\0'; i++)
    {
        char ch = input[i];
        if (ch == '\'' && !in_double_quotes)
        {
            in_single_quotes = !in_single_quotes;
            continue;
        }
        if (ch == '"' && !in_single_quotes)
        {
            in_double_quotes = !in_double_quotes;
            continue;
        }
        if (in_single_quotes || in_double_quotes || (ch != '\'' && ch != '"')) {
            buffer[buffer_index++] = ch;
        }
    }
    buffer[buffer_index] = '\0';
    printf("%s\n", buffer);
}
//
// Implementer le -n
//              faire en sorte que echo -n -n -n -n == echo -n
// gerer la derniere new line
// couper en sous fonctions
//
//
//
//
int main() {
    ft_echo("echo \"'test'\" \"123\"");
    return 0;
}