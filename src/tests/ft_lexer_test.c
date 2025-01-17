/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:01 by amine             #+#    #+#             */
/*   Updated: 2025/01/17 17:58:36 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// Function prototypes
char *trim_input(char *input);
int count_tokens(char *input);
char **split_whitespace(char *input);


void print_tokens(char **tokens)
{
    int i = 0;
    while (tokens[i])
    {
        printf("Token %d: '%s'\n", i, tokens[i]);
        i++;
    }
}

int main()
{
    char input1[] = "   Hello, 'World!   ";
    char input2[] = "  'dsfsdf' This is a test string.   ";
    char input3[] = "NoSpacesHere";
    char input4[] = "   ";
    char input5[] = "  \"Hello, World!\"   ";
    char input6[] = "  'Hello, World!'   ";
    char input7[] = "command1 | command2";
    char input8[] = "command1 > output.txt";
    char input9[] = "command1 >> output.txt";
    char input10[] = "command1 < input.txt";
    char input11[] = "echo \"    ";

    char *inputs[] = {input1, input2, input3, input4, input5, input6, input7, input8, input9, input10, input11};
    int num_inputs = sizeof(inputs) / sizeof(inputs[0]);

    for (int i = 0; i < num_inputs; i++)
    {
        printf("Original: '%s'\n", inputs[i]);
        char **tokens = split_whitespace(inputs[i]);
        print_tokens(tokens);
        printf("\n");
        // Free allocated memory for tokens
        free(tokens);
    }

    return 0;
}
