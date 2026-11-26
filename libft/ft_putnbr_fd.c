/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:29:14 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/26 11:03:45 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recursive(long int n, int fd)
{
	char	c;

	c = (n % 10) + '0';
	if (n > 0)
	{
		ft_recursive(n / 10, fd);
		write(fd, &c, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;

	nbr = (long int)n;
	if (nbr == 0)
		write(fd, "0", 1);
	else if (nbr < 0)
	{
		write(fd, "-", 1);
		nbr = nbr * (-1);
	}
	if (nbr > 0)
		ft_recursive(nbr, fd);
}
