/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 09:36:47 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 10:01:17 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_islittle(const char *big, const char *little, int i)
{
	if (*little == '\0')
		return (1);
	if (*big == *little && i > 0)
	{
		return (ft_islittle(big + 1, little + 1, i - 1));
	}
	else
		return (0);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;

	ptr = (char *)big;
	if (*little == '\0')
		return (ptr);
	while (len > 0)
	{
		if (ft_islittle(ptr, little, len) == 1)
		{
			return (ptr);
		}
		ptr = ptr + 1;
		len--;
	}
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>
//     const char    s1[] = "je susuiss cool";
//     const char    s2[] = "suis";

//     printf("%s", ft_strnstr(s1, s2, 10));
// }