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

static char	**init_minimal_env(void)
{
	char	**env_copy;
	char	*cwd;

	env_copy = malloc(4 * sizeof(char *));
	if (!env_copy)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(env_copy), NULL);
	env_copy[0] = ft_strjoin("PWD=", cwd);
	env_copy[1] = ft_strdup("SHLVL=1");
	env_copy[2] = ft_strdup("_=/usr/bin/env");
	env_copy[3] = NULL;
	free(cwd);
	if (!env_copy[0] || !env_copy[1])
		return (free_args(env_copy), NULL);
	return (env_copy);
}

static char	**copy_existing_env(char **envp)
{
	char	**env_copy;
	int		i;
	int		len;

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
			return (free_args(env_copy), NULL);
	}
	env_copy[i] = NULL;
	return (env_copy);
}

char	**copy_envp(char **envp)
{
	if (!envp || !*envp)
		return (init_minimal_env());
	return (copy_existing_env(envp));
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
int add_to_export(char *var, t_data *data)
{
	size_t  i;
	size_t  export_len;
	char	**new_export;

	export_len = 0;
	while (data->export && data->export[export_len])
		export_len++;

	new_export = malloc((export_len + 2) * sizeof(char *));
	if (!new_export)
		return (-1);

	for (i = 0; i < export_len; i++)
		new_export[i] = data->export[i];

	new_export[i] = ft_strdup(var);
	if (!new_export[i])
	{
		free(new_export);
		return (-1);
	}
	new_export[i + 1] = NULL;
	free(data->export);
	data->export = new_export;
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

void	print_export_list(char **export_list)
{
	int		i;
	char	*equal_sign;
	char	*var;
	char	*value;

	if (!export_list)
		return;
	i = -1;
	while (export_list[++i])
	{
		equal_sign = ft_strchr(export_list[i], '=');
		if (equal_sign)
		{
			var = ft_strndup(export_list[i], equal_sign - export_list[i]);
			value = equal_sign + 1;
			printf("export %s=\"%s\"\n", var, value);
			free(var);
		}
		else
			printf("export %s\n", export_list[i]);
	}
}

int ft_export(char *str, t_data *data)
{
	char *equal_sign;
	char *var;
	char *value;

	if (!str || !*str)
	{
		print_export_list(data->export);
		return (0);
	}
	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
	{
		var = ft_substr(str, 0, equal_sign - str);
		value = equal_sign + 1;
		ft_set_env(var, value, data);
		add_to_export(str, data);
		free(var);
	}
	else
	{
		add_to_export(str, data);
	}
	return (0);
}

static char	**init_minimal_export(void)
{
	char	**export_copy;
	char	*cwd;

	export_copy = malloc(4 * sizeof(char *));
	if (!export_copy)
		return (NULL);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (free(export_copy), NULL);
	export_copy[0] = ft_strjoin("PWD=", cwd);
	export_copy[1] = ft_strdup("SHLVL=1");
	export_copy[2] = ft_strdup("OLDPWD");
	export_copy[3] = NULL;
	free(cwd);
	if (!export_copy[0] || !export_copy[1] || !export_copy[2])
		return (free_args(export_copy), NULL);
	return (export_copy);
}

char	**copy_export_list(char **envp)
{
	if (!envp || !*envp)
		return (init_minimal_export());
	return (copy_existing_env(envp));
}

