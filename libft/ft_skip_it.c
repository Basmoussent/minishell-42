/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skip_it.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 15:18:48 by bdenfir           #+#    #+#             */
/*   Updated: 2025/01/15 16:17:33 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_skipt_it(char *str, int c)
{
	int i;
	int len;

	if (!str)
		return (NULL);
	i	= 0;
	len = ft_strlen(str);
	while (i <= len && str[i] != c)
		i++;
	while (i <= len && str[i] == c)
		i++;
	if (str[i] == '\0')
		return (str);
	return (&str[i]);
}
