/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 11:39:03 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 10:11:55 by ltalpain         ###   ########.fr       */
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

// int main(void)
// {
//     #include <stdio.h>

//     char    dest[10];
//     char    src[] = "Luka";

//     printf("%d",ft_strlcpy(dest, src, 7));
//     printf ("\n%s", dest);
// }