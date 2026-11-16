/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 09:46:42 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 10:10:25 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

unsigned char	*ft_geta(unsigned char *a, const unsigned char *b, size_t n)
{
	size_t	i;

	if (a < b)
	{
		i = 0;
		while (i < n)
		{
			a[i] = b[i];
			i++;
		}
	}
	else
	{
		while (n > 0)
		{
			n--;
			a[n] = b[n];
		}
	}
	return (a);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*a;
	const unsigned char	*b;

	a = (unsigned char *)dest;
	b = (const unsigned char *)src;
	if (n == 0 || (a == b))
		return (dest);
	return (ft_geta(a, b, n));
}

// int main(void)
// {
//     #include <stdio.h>
//     char buf[] = "abcdef";
//     ft_memmove(buf + 2, buf, 4);
//     printf("%s", buf);
// }