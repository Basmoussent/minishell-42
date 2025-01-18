/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:01 by amine             #+#    #+#             */
/*   Updated: 2025/01/18 03:27:41 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>

// Function prototypes
char *trim_input(char *input);
int count_tokens(char *input);
char **split_whitespace(char *input);
enum s_token classify_token(char *token);
t_ast_node *parse_tokens(char **tokens, t_data *data);
char *expand_variable(char *input, t_data *data);
char **copy_envp(char **envp);
void free_args(char **args);

void print_ast(t_ast_node *node, int level)
{
    if (!node)
        return;
    for (int i = 0; i < level; i++)
        printf("  ");
    printf("Node (Type: %d, Value: '%s')\n", node->type, node->value);
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}

void free_ast(t_ast_node *node)
{
    if (!node)
        return;
    free_ast(node->left);
    free_ast(node->right);
    free(node->value);
    free(node);
}

int test(int argc, char **argv, char **envp)
{
    if (argc != 1 || !argv)
    {
        printf("Usage: ./ft_lexer_test\n");
        return 1;
    }
    t_data data;
    data.envp = copy_envp(envp);

    char *input5 = "echo dsqd$VAR_NAME$VAR_NAMEsdq";

        char **tokens = split_whitespace(input5);
        t_ast_node *ast = parse_tokens(tokens, &data);

        printf("AST:\n");
        print_ast(ast, 0);
        printf("\n");

        // Free allocated memory for tokens and AST
        free(tokens);
        free_ast(ast);
    

    free_args(data.envp);
    return 0;
}