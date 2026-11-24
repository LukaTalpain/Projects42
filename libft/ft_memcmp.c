/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 15:00:28 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/24 11:21:45 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	i = 0;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		if (str1[i] - str2[i] != 0)
			return (str1[i] - str2[i]);
		n--;
		if (n <= 0)
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}
