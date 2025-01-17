/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lexer_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 14:52:01 by amine             #+#    #+#             */
/*   Updated: 2025/01/17 21:27:28 by amine            ###   ########.fr       */
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
t_ast_node *parse_tokens(char **tokens);

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

int main()
{
    char *input1 = "echo mdr | cd libft";
    
        printf("Original: '%s'\n", input1);
        char **tokens = split_whitespace(input1);
        t_ast_node *ast = parse_tokens(tokens);

        printf("AST:\n");
        print_ast(ast, 0);
        printf("\n");
        printf("%s", tokens[0]);
        // Free allocated memory for tokens and AST
        free(tokens);
        //free_ast(ast);
    

    return 0;
}