/* ************************************************************************** */
/*									  */
/*							:::	 ::::::::   */
/*   ft_lexer_test.c									:+:   :+:	:+:   */
/*						  +:+ +:+	   +:+	*/
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+	*/
/*						+#+#+#+#+#+   +#+	 */
/*   Created: 2025/01/17 14:52:01 by amine	   #+#  #+#		  */
/*   Updated: 2025/01/20 17:33:31 by bdenfir		  ###   ########.fr	*/
/*									  */
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

void print_branch(const char *prefix, int is_left) {
    printf("%s", prefix);
    if (is_left)
        printf("├── ");
    else
        printf("└── ");
}

// Recursive function to display the AST as a tree
void print_ast(t_ast_node *node, const char *prefix, int is_left)
{
    if (!node)
        return;
    print_branch(prefix, is_left);
    printf(TYPE_COLOR "Node (Type: %d" COLOR_RESET ", " VALUE_COLOR "Value: '%s'" COLOR_RESET ")\n",
           node->type, node->value ? node->value : "NULL");
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s", prefix, is_left ? "│   " : "    ");
    if (node->left || node->right) {
        print_ast(node->left, new_prefix, 1);
        print_ast(node->right, new_prefix, 0);
    }
}

int ft_lexer_test(int argc, char **argv, char **envp)
{
	if (argc != 1 || !argv)
	{
		printf("Usage: ./ft_lexer_test\n");
		return 1;
	}
	t_data data;
	data.envp = copy_envp(envp);
	char *input5 = "echo dsqd > test1 | echo";
	char **tokens = split_whitespace(input5);
	t_ast_node *ast = parse_tokens(tokens, &data);
	printf("AST:\n");
	print_ast(ast, "",0);
	printf("\n");
	free(tokens);
	free_ast(ast);
	free_args(data.envp);
	return 0;
}