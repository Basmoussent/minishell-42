/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akassous <akassous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 02:10:34 by amine             #+#    #+#             */
/*   Updated: 2025/01/27 15:02:37 by akassous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *name, t_data *data)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (data->envp[i])
	{
		if (ft_strncmp(data->envp[i], name, len) == 0
			&& data->envp[i][len] == '=')
			return (data->envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*extract_var_name(char *start)
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

char	*expand_single_variable(char *input, t_data *data)
{
	char	*start;
	char	*end;
	char	*var_name;
	char	*var_value;
	char	*result;

	start = ft_strchr(input, '$');
	if (!start)
		return (ft_strdup(input));
	end = start + 1;
	/*if (end == '?')
		return (get_return_value(prev));*/
	while (*end && (ft_isalnum(*end) || *end == '_'))
		end++;
	var_name = extract_var_name(start);
	var_value = get_env_value(var_name, data);
	free(var_name);
	if (!var_value)
		var_value = "";
	result = replace_variable(input, start, var_value, end);
	return (result);
}

char *expand_all_variables(char *input, t_data *data)
{
    char    *result;
    char    *temp;
    bool    in_single_quotes;
    size_t  i;

    result = ft_strdup(input);
    if (!result)
        return (NULL);
    in_single_quotes = false;
    i = 0;
    while (result[i] != '\0')
    {
        if (result[i] == '\'')
            in_single_quotes = !in_single_quotes;
        if (!in_single_quotes && result[i] == '$')
        {
            temp = expand_single_variable(result, data);
            free(result);
            result = temp;
            i = 0;
        }
        else
            i++;
    }
    return (result);
}
