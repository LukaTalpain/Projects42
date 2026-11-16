/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 10:55:03 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/09 16:01:14 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int input)
{
	if ((input >= '0' && input <= '9') || ((input >= 'a' && input <= 'z')
			|| (input >= 'A' && input <= 'Z')))
		return (1);
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>

//     printf("%d", ft_isalnum('*'));
// }