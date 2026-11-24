/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 10:00:29 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/24 11:51:14 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	originalsize;
	size_t	space;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	originalsize = ft_strlen(dst);
	if (size <= originalsize)
		space = 0;
	else
		space = size - originalsize - 1;
	if (size < originalsize)
		return (size + ft_strlen(src));
	while (space > 0 && src[i])
	{
		dst[originalsize + i] = src[i];
		i++;
		space--;
	}
	dst[originalsize + i] = '\0';
	return (originalsize + ft_strlen(src));
}
