/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amine <amine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 02:10:34 by amine             #+#    #+#             */
/*   Updated: 2025/01/18 02:57:11 by amine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_env_value(char *name, t_data *data)
{
    int i;
    size_t len = strlen(name);

    for (i = 0; data->envp[i] != NULL; i++)
    {
        if (strncmp(data->envp[i], name, len) == 0 && data->envp[i][len] == '=')
            return data->envp[i] + len + 1;
    }
    return NULL;
}

char *extract_var_name(char *start)
{
	char	*end;
	char	*value;

	end = start + 1;
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
    value = ft_strndup(start + 1, end - start - 1);
	if (!value)
		return (NULL);
	return (value);
}

char	*replace_variable(char *input, char *start, char *var_value, char *end)
{
	size_t	len;
	char	*result;

	len = ft_strlen(input) - (end - start) + ft_strlen(var_value);
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_strlcpy(result, input, start - input + 1);
	result[start - input] = '\0';
	ft_strlcat(result, var_value, len + 1);
	ft_strlcat(result, end, len + 1);
	return (result);
}

char *expand_variable(char *input, t_data *data)
{
    char	*start;
    char	*end;
    char	*var_name;
    char	*var_value;
    char	*result;
    char	*temp;

	result = ft_strdup(input);
	if (!result)
		return (NULL);
	while ((start = ft_strchr(result, '$')))
	{
		end = start + 1;
		while (*end && (ft_isalnum(*end) || *end == '_'))
			end++;
		var_name = extract_var_name(start);
		var_value = get_env_value(var_name, data);
		free(var_name);
		if (!var_value)
			var_value = "";
		temp = replace_variable(result, start, var_value, end);
		free(result);
		result = temp;
	}
	return (result);
}
