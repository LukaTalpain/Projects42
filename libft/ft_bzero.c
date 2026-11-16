/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 09:26:18 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 09:58:09 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n > 0)
	{
		*ptr = '\0';
		ptr++;
		n--;
	}
}

// int main(void)
// {
//     #include <stdio.h>

//     char    ptr[50] = "Coucou";

//     printf("%s", ptr);

//     ft_bzero(ptr + 2, 3);

//     printf("\n%s", ptr);
// }