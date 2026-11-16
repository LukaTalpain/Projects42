/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:15:34 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/10 09:43:15 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int letter)
{
	if (letter >= 'a' && letter <= 'z')
		return (letter - 32);
	return (letter);
}

// int main(void)
// {
//     #include <stdio.h>

//     printf("%c", ft_toupper('a'));
// }