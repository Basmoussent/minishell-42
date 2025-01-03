/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bdenfir <bdenfir@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:13:19 by bdenfir           #+#    #+#             */
/*   Updated: 2024/11/16 11:40:56 by bdenfir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*

calloc is a functio from malloc(3), it is used to allocate
memory and overwrite memory and set it to 0.

the function takes nmemb (numbers of memory box), and size (sizeof(elemets))
parameters.

return a pointer to the allocated area.
*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void		*new;
	size_t		i;

	new = (void *) malloc(size * nmemb);
	if (!new)
		return (NULL);
	i = 0;
	while (i < size * nmemb)
	{
		*(unsigned char *)(new + i) = 0;
		i++;
	}
	return (new);
}
