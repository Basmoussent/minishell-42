/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 01:39:48 by bdenfir           #+#    #+#             */
/*   Updated: 2025/02/25 14:26:31 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prints error message for invalid export variable
int	print_export_error(int error, char *arg)
{
	if (error == -1)
		ft_putstr_fd("export: not valid in this context: ", STDERR_FILENO);
	while (*arg && (*arg != '=' || error == -3))
		write(STDERR_FILENO, arg++, 1);
	write(STDERR_FILENO, "\n", 1);
	return (STDERR_FILENO);
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

int	ft_export(char *str, t_data *data)
{
	char	*equal_sign;
	char	*var;
	char	*value;
	char	**vars;
	int		i;

	if (!str || !*str)
	{
		print_export_list(data->export);
		return (0);
	}
	vars = ft_split(str, ' ');
	i = 0;
	while (vars[i])
	{
		equal_sign = ft_strchr(vars[i], '=');
		if (equal_sign)
		{
			var = ft_substr(vars[i], 0, equal_sign - vars[i]);
			value = equal_sign + 1;
			ft_set_env(var, value, data);
			if (!is_in_export_list(var, data->export))
				add_to_export(vars[i], data);
			free(var);
		}
		else
		{
			if (!is_in_export_list(vars[i], data->export))
				add_to_export(vars[i], data);
		}
		i++;
	}
	free_args(vars);
	return (0);
}
