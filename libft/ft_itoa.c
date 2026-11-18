/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:38:28 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/18 09:43:36 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_unitcounter(long int n)
{
	int	cnt;

	cnt = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		cnt++;
		n = n * (-1);
	}
	while (n >= 1)
	{
		n = n / 10;
		cnt++;
	}
	return (cnt);
}

static void	ft_write(long int nb, int size, char *str)
{
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * (-1);
	}
	size--;
	while (nb >= 1)
	{
		str[size] = (nb % 10) + '0';
		nb = nb / 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char		*str;
	int			size;
	long int	nb;

	nb = n;
	size = ft_unitcounter(nb);
	str = malloc(sizeof(char) * (size + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	if (nb == 0)
	{
		str[0] = '0';
		return (str);
	}
	ft_write(nb, size, str);
	return (str);
}
