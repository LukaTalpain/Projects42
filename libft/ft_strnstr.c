/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 09:36:47 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/18 09:26:36 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static int	ft_islittle(const char *big, const char *little, size_t len)
{
	if (*little == '\0')
		return (1);
	if (*big == '\0' || len == 0)
		return (0);
	if (*big == *little)
		return (ft_islittle(big + 1, little + 1, len - 1));
	return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] != '\0' && i < len)
	{
		if (ft_islittle(big + i, little, len - i))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
