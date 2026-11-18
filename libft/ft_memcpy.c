/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 09:46:55 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/18 10:29:13 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*a;
	const unsigned char	*b;
	int					i;

	a = (unsigned char *)dest;
	b = (const unsigned char *)src;
	i = 0;
	while (n > 0)
	{
		a[i] = b[i];
		i++;
		n--;
	}
	return (a);
}

// int main(void)
// {
//     #include <stdio.h>
//     char buf[] = "abcdef";
//     ft_memcpy(buf + 2, buf, 4);
//     printf("%s", buf);
// }