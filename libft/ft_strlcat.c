/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 10:00:29 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 10:14:18 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	originalsize;
	int		space;

	i = 0;
	originalsize = ft_strlen(dst);
	space = size - originalsize - 1;
	if (size == 0)
		return (ft_strlen(src));
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
