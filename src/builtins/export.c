#include "minishell.h"

// Prints error message for invalid export variable
static int print_error(int error, char *arg)
{
	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR_FILENO);
	while (*arg && (*arg != '=' || error == -3))
		write(STDERR_FILENO, arg++, 1);
	write(STDERR_FILENO, "\n", 1);
	return (STDERR_FILENO);
}

// Creates a copy of the environment
char	**copy_envp(char **envp)
{
	int		i;
	int		len;
	char	**env_copy;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	env_copy = malloc((len + 1) * sizeof(char *));
	if (!env_copy)
		return (NULL);
	i = -1;
	while (++i < len)
	{
		env_copy[i] = ft_strdup(envp[i]);
		if (!env_copy[i])
		{
			while (i-- > 0)
				free(env_copy[i]);
			free(env_copy);
			return (NULL);
		}
	}
	env_copy[i] = NULL;
	return (env_copy);
}

int	is_valid_varname(char *var)
{
	int	i;

	if (!(var[0] == '_' || ft_isalpha(var[0])))
		return (0);
	i = 1;
	while (var[i])
	{
		if (!(var[i] == '_' || ft_isalnum(var[i])))
			return (0);
		i++;
	}
	return (1);
}

static char	*join_var_value(char *var, char *value)
{
	char	*new_entry;
	char	*full_entry;

	new_entry = ft_strjoin(var, "=");
	if (!new_entry)
		return (NULL);
	full_entry = ft_strjoin(new_entry, value);
	free(new_entry);
	return (full_entry);
}

int	ft_export(char *str, t_data *data)
{
	char	*equal_sign;
	char	*var;
	char	*value;

	if (!str || !*str || occur(str, '=') == 0)
		return (KO);
	while (*str)
	{
		equal_sign = ft_strnstr(str, "=", ft_strlen(str));
		var = ft_strdup(str);
		value = "";
		if (equal_sign)
		{
			var[equal_sign - str] = '\0';
			value = equal_sign + 1;
		}
		while (*str && *str != ' ')
			str++;
		if (*str == ' ')
			*str++ = '\0';
		ft_set_env(var, value, data);
		free(var);
	}
	return (0);
}

int	add_new_var_to_env(char *full_entry, t_data *data)
{
	size_t	env_len;
	char	**new_envp;
	size_t	i;

	env_len = 0;
	while (data->envp[env_len])
		env_len++;
	new_envp = malloc((env_len + 2) * sizeof(char *));
	if (!new_envp)
	{
		free(full_entry);
		return (-1);
	}
	i = 0;
	while (i < env_len)
	{
		new_envp[i] = data->envp[i];
		i++;
	}
	new_envp[i] = full_entry;
	new_envp[i + 1] = NULL;
	free(data->envp);
	data->envp = new_envp;
	return (0);
}
int ft_set_env(char *var, char *value, t_data *data)
{
	size_t  i;
	char	*full_entry;

	if (!var || !value || !data || !data->envp)
		return (-1);
	if (!is_valid_varname(var))
		return (print_error(-1, var));
	full_entry = join_var_value(var, value);
	if (!full_entry)
		return (-1);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], var, ft_strlen(var)) == 0 &&
			data->envp[i][ft_strlen(var)] == '=')
		{
			free(data->envp[i]);
			data->envp[i] = full_entry;
			return (0);
		}
		i++;
	}
	return (add_new_var_to_env(full_entry, data));
}
