/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   print_ast.c										:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/25 15:00:00 by bdenfir		   #+#	#+#			 */
/*   Updated: 2025/03/01 07:50:54 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

void	print_branch(const char *prefix, int is_left)
{
	printf("%s", prefix);
	if (is_left)
		printf("├── ");
	else
		printf("└── ");
}

// Recursive function to display the AST as a tree
void	print_ast(t_ast_node *node, char *prefix, int is_left)
{
	char	new_prefix[256];
	
	if (!node)
		return;
	print_branch(prefix, is_left);
	printf(TYPE_COLOR "Node (Type: %d" COLOR_RESET ", " VALUE_COLOR "Value: '%s'" COLOR_RESET ")\n",
		   node->type, node->value ? node->value : "NULL");
	ft_strcpy(new_prefix, prefix);
	strcat(new_prefix, is_left ? "│   " : "	");
	if (is_left)
		ft_strlcat(new_prefix, "|   ", ft_strlen(new_prefix) + 1);
	else
		ft_strlcat(new_prefix, "	", ft_strlen(new_prefix) + 1);
	if (node->left || node->right) {
		print_ast(node->left, new_prefix, 1);
		print_ast(node->right, new_prefix, 0);
	}
}
