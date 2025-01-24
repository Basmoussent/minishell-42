/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comnpress_ast.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:50:10 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/24 13:51:28 by bdenfir          ###   ########.fr       */
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
        return ;

    compress_ast(node->left);
    compress_ast(node->right);

    if (node->type == 0 && node->right && node->right->type == 0)
    {
        printf("Compressing: '%s' <- '%s'\n", node->value, node->right->value);

        char *new_value = concat_with_space(node->value, node->right->value);
        free(node->value);
        node->value = new_value;

        t_ast_node *temp = node->right;
        node->right = temp->right;
        free(temp->value);
        free(temp);
    }
}

