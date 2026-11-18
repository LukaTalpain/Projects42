/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 11:55:02 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/18 10:29:36 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = s;
	while (n > 0)
	{
		n--;
		ptr[i] = (char)c;
		i++;
	}
	return (ptr);
}

// int main(void)
// {
//     #include <stdio.h>
//     char    ptr[50];
//     ft_memset(ptr, 'c', 5);
//     printf("%s", ptr);
// }