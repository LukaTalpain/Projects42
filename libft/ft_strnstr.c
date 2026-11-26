/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 09:36:47 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/26 11:10:02 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_islittle(const char *big, const char *little, size_t len)
{
	if (*little == '\0')
		return (1);
	if (len == 0 || *big == '\0' )
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
	if (big == NULL)
		return (NULL);
	i = 0;
	while (i < len && big[i] != '\0')
	{
		if (ft_islittle(big + i, little, len - i))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
