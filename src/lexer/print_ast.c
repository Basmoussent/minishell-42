/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 15:00:00 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/25 15:06:21 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void print_branch(const char *prefix, int is_left) {
    printf("%s", prefix);
    printf(is_left ? "├── " : "└── ");
}

// Recursive function to display the AST as a tree
void print_ast(t_ast_node *node, char *prefix, int is_left)
{
    if (!node)
        return;

    print_branch(prefix, is_left);
    printf(TYPE_COLOR "Node (Type: %d" COLOR_RESET ", " VALUE_COLOR "Value: '%s'" COLOR_RESET ")\n",
           node->type, node->value ? node->value : "NULL");
    char new_prefix[256];
    ft_strcpy(new_prefix, prefix);
    strcat(new_prefix, is_left ? "│   " : "    ");
    if (node->left || node->right) {
        print_ast(node->left, new_prefix, 1);
        print_ast(node->right, new_prefix, 0);
    }
}
