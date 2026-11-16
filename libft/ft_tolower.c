/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:16:22 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/10 09:43:40 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_tolower(int letter)
{
	if (letter >= 'A' && letter <= 'Z')
		return (letter + 32);
	return (letter);
}

// int main(void)
// {
//     #include <stdio.h>

//     printf("%c", ft_tolower('A'));
// }