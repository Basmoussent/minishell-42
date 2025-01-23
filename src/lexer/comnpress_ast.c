/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comnpress_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:50:10 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/23 20:09:59 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *concat_with_space(const char *str1, const char *str2)
{
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    char *result = malloc(len1 + len2 + 2);
    if (!result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    strcpy(result, str1);
    result[len1] = ' ';
    strcpy(result + len1 + 1, str2);
    return result;
}

void compress_ast(t_ast_node *node)
{
    if (!node)
        return;

    compress_ast(node->left);
    compress_ast(node->right);

    // Ensure the node is a command and the right node is an argument
    if (node->type == 0 && node->right && node->right->type == 0)
    {
        printf("Linking command: '%s' with argument: '%s'\n", node->value, node->right->value);

        // Link the command node to its argument node
        t_ast_node *arg_node = node->right;
        node->right = arg_node->right;
        arg_node->right = NULL;

        // Attach the argument node to the command node's arguments list
        if (!node->left)
        {
            node->left = arg_node;
        }
        else
        {
            t_ast_node *last_arg = node->left;
            while (last_arg->right)
                last_arg = last_arg->right;
            last_arg->right = arg_node;
        }
    }
}