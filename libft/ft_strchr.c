/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:31:07 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/10 10:01:09 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *str, int find)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == (char)find)
			return ((char *)(str + i));
		i++;
	}
	if (str[i] == (char)find)
		return ((char *)(str + i));
	return (0);
}

// int main(void)
// {
//     #include <stdio.h>

//     char    str[] = "je suis cool";

//     printf("%s", ft_strchr(str, 'c'));
// }