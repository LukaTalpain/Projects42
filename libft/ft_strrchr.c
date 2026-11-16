/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 14:37:52 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/10 11:08:04 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *str, int find)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = 0;
	while (str[i])
	{
		if (str[i] == (char)find)
			ptr = (char *)str + i;
		i++;
	}
	if (str[i] == (char)find)
		ptr = (char *)str + i;
	return (ptr);
}

// int main(void)
// {
//     #include <stdio.h>

//     char    str[] = "je suis cool";

//     printf("%s", ft_strrchr(str, 's'));
// }