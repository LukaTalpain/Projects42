/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 09:57:58 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/19 17:21:50 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *arg)
{
	int				i;
	unsigned int	nb;
	int				negative;

	i = 0;
	negative = 0;
	nb = 0;
	while (arg[i] == ' ' || (arg[i] >= '\t' && arg[i] <= '\r'))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			negative = 1;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		nb = (nb * 10) + arg[i] - '0';
		i++;
	}
	if (negative == 1)
		nb = nb * (-1);
	return (nb);
}
