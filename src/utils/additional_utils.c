/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   additional_utils.c								 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: bdenfir <bdenfir@42.fr>					+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/02/17 16:52:45 by akassous		  #+#	#+#			 */
/*   Updated: 2025/02/18 13:23:16 by bdenfir		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quotes(char *input)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*result;

	if (!input)
		return (NULL);
	len = ft_strlen(input);
	result = (char *)malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			i++;
			continue ;
		}
		result[j++] = input[i++];
	}
	result[j] = '\0';
	return (result);
}

int	can_expand(char *rslt)
{
	return (rslt[1] && !is_space(rslt[1]) && rslt[1] != '"' && rslt[1] != '\'');
}

char	*expand_status(int status, char *input)
{
	char	*status_str;
	char	*result;
	size_t	status_len;
	size_t	input_len;

	status_str = ft_itoa(status);
	if (!status_str)
		return (NULL);
	if (*input == '"' || *input == '\'')
		return (status_str);
	status_len = ft_strlen(status_str);
	input_len = ft_strlen(input);
	result = (char *)malloc(status_len + input_len + 1);
	if (!result)
	{
		free(status_str);
		return (NULL);
	}
	ft_strlcpy(result, status_str, status_len + 1);
	ft_strlcat(result, input, status_len + input_len + 1);
	free(status_str);
	return (result);
}
