/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   export.c										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/01/04 14:49:02 by bdenfir		   #+#	#+#			 */
/*   Updated: 2025/01/04 18:16:53 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	int		i;
	int		len;
	char	**env_copy;

	len = 0;
	while (envp[len] != NULL)
		len++;
	env_copy = malloc((len + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = 0;
	while (i < len)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (i > 0)
				free(env_copy[--i]);
			free(env_copy);
			return (NULL);
		}
		i++;
	}
	env_copy[i] = NULL;
	return (env_copy);
}

void free_args(char **envp)
{
	int	i = 0;

	while (envp[i])
		free(envp[i++]);
	free(envp);
}

int	is_valid_varname(char *var)
{
	int	i;
	
	i = 0;
	if (!(var[i] == '_' || (var[i] >= 'A' && var[i] <= 'Z')
		|| (var[i] >= 'a' && var[i] <= 'z')))
		return (0);
	i++;
	while (var[i])
	{
		if (!(var[i] == '_' || (var[i] >= 'A' && var[i] <= 'Z')
			|| (var[i] >= 'a' && var[i] <= 'z') || (var[i] >= '0'
			&& var[i] <= '9')))
			return (0);
		i++;
	}
	return (1);
}

int	ft_export(char *str, t_data *data)
{
	char	*var;
	char	*value;
	char	*equal_sign;

	if (!str || !*str)
		return (KO);
	while (str && *str)
	{
		equal_sign = ft_strnstr(str, "=", ft_strlen(str));
		if (equal_sign)
		{
			var = ft_strdup(str);
			var[equal_sign - str] = '\0';
			value = equal_sign + 1;
		}
		else
		{
			var = ft_strdup(str);
			value = "";
		}
		while (*str && *str != ' ')
			str++;
		if (*str == ' ')
			*str++ = '\0';
		printf("%s - %s\n", var, value);
		ft_set_env(var, value, data);
		free(var);
	}
	return (0);
}

int	ft_set_env(char *var, char *value, t_data *data)
{
	size_t		i;
	char	*new_entry;
	char	**new_envp;
	size_t	env_len;

	if (!var || !value || !data || !data->envp)
		return (-1);

	new_entry = ft_strjoin(ft_strjoin(var, "="), value);
	if (!new_entry)
		return (-1);
	for (i = 0; data->envp[i]; i++)
	{
		if (ft_strncmp(data->envp[i], var, ft_strlen(var)) == 0 &&
			data->envp[i][ft_strlen(var)] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = new_entry;
			return (0);
		}
	}
	env_len = 0;
	while (data->envp[env_len])
		env_len++;

	new_envp = malloc((env_len + 2) * sizeof(char *));
	if (!new_envp)
		return (free(new_entry), -1);

	for (i = 0; i < env_len; i++)
		new_envp[i] = data->envp[i];

	new_envp[env_len] = new_entry;
	new_envp[env_len + 1] = NULL;

	free(data->envp);

	data->envp = new_envp;
	return (0);
}
