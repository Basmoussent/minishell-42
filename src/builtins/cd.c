/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   cd.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/20 14:49:39 by bdenfir		   #+#	#+#			 */
/*   Updated: 2025/01/20 15:02:05 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

// Function to print error messages
static void print_error(char *path, int code)
{
	if (code == -1)
		printf(COLOR_RED "cd: %s: No such file or directory\n" COLOR_RESET, path);
	else if (code == -2)
		printf(COLOR_RED "cd: %s: Not a directory\n" COLOR_RESET, path);
	else if (code == -3)
		printf(COLOR_RED "cd: Failed to get current working directory\n" COLOR_RESET);
	else if (code == -4)
		printf(COLOR_RED "cd: Failed to export new PWD" COLOR_RESET);
}

// Function to change the current working directory
int	ft_cd(char *path, t_data *data)
{
	char	*old_pwd;
	char	*pwd;
	char	*str;

	if (!validate_command(path) || !path)
		return (KO);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (print_error(path, -3), KO);
	if (chdir(path) == -1)
		return (print_error(path, -1), free(old_pwd), KO);
	pwd = ft_strjoin("PWD=", path);
	if (!pwd || ft_export(pwd, data) != OK)
		return (print_error(path, -4), free(pwd), free(old_pwd), KO);
	str = ft_strjoin("OLDPWD=", old_pwd);
	if (!str || ft_export(str, data) != OK)
		return (print_error(path, -4),free(old_pwd), free(str), free(pwd), KO);
	free(pwd);
	free(old_pwd);
	free(str);
	return (OK);
}
