/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 11:28:08 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/09 16:01:24 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int print)
{
	if (print >= 32 && print <= 126)
		return (1);
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>

//     printf("%d",ft_isprint('\n'));
// }