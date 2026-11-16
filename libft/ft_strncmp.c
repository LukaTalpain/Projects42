/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:44:52 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 10:01:11 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)s1;
	b = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (a[i] && b[i])
	{
		if (a[i] - b[i] != 0)
			return (a[i] - b[i]);
		n--;
		if (n <= 0)
			return (a[i] - b[i]);
		i++;
	}
	return (a[i] - b[i]);
}

// int main(void)
// {
//     #include <stdio.h>
//     char    s1[] = "coob";
//     char    s2[] = "cooa";

//     printf("%d", ft_strncmp(s1, s2));
// }