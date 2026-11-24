/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:39:03 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/24 11:20:45 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	if (size == 1)
	{
		dst[0] = '\0';
		return (ft_strlen(src));
	}
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	if (i >= size)
		dst[i - 1] = '\0';
	else
		dst[i] = '\0';
	return (ft_strlen(src));
}
