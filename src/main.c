/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/03 15:42:04 by bdenfir		   #+#	#+#			 */
/*   Updated: 2025/01/14 22:30:22 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[], char *envp[])
{
	t_data *data = malloc(sizeof(t_data *));

	printf("Program: %s\n", av[ac - 1]);
	data->envp = copy_envp(envp);
	if (!data->envp)
	{
		fprintf(stderr, "Error: Failed to copy environment variables.\n");
		return (1);
	}
	printf("Testing ft_unset:\n");
	ft_export("unset=caca", data);
	ft_unset("TERM\\ROGRAM", data);
	ft_env(data->envp);
	free_args(data->envp);

	return (0);
}


