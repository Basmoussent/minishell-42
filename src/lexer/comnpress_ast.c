/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   comnpress_ast.c                                    :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2025/01/23 19:50:10 by bdenfir           #+#  #+#          */
/*   Updated: 2025/01/24 15:54:23 by bdenfir          ###   ########.fr    */
/*                                      */
/* ************************************************************************** */

#include "minishell.h"

void	split_command_arg(t_ast_node *node)
{
	char *arg;
	char *space;

	space = ft_strchr(node->value, ' ');
	if (!space)
		return ;
	arg = ft_strdup(space);
	ft_strchr(node->value, ' ')[0] = '\0';
	if (arg)
	{
		*arg = '\0';
		node->right = create_ast_node(0, arg + 1);
	}

}

void compress_ast(t_ast_node *node)
{
    if (!node)
        return;

    if (node->type == 0)
        split_command_arg(node);
    compress_ast(node->left);
    compress_ast(node->right);
}
