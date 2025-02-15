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
static void	print_error(int code)
{
	if (code == -1)
		ft_putstr_fd("cd: No such file or directory\n", 2);
	else if (code == -2)
		ft_putstr_fd("cd: Not a directory\n", 2);
	else if (code == -3)
		ft_putstr_fd("cd: Failed to get working directory\n", 2);
}

static int	update_pwd(char *old_pwd, t_data *data)
{
	char	*new_pwd;
	int		ret;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (free(old_pwd), KO);
	if (ft_set_env("PWD", new_pwd, data) != OK)
	{
		free(new_pwd);
		return (KO);
	}
	ret = ft_set_env("OLDPWD", old_pwd, data);
	free(new_pwd);
	if (ret != OK)
		return (KO);
	return (OK);
}

int	ft_cd(char *path, t_data *data)
{
	char	*old_pwd;
	int		ret;

	if (!path || chdir(path) == -1)
		return (print_error(-1), KO);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (print_error(-3), KO);
	ret = update_pwd(old_pwd, data);
	free(old_pwd);
	return (ret);
}

