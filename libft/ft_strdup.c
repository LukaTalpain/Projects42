/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 10:00:18 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/19 17:14:44 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*str;
	int		s_lenght;
	int		i;

	s_lenght = ft_strlen(s);
	str = malloc(s_lenght + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < s_lenght)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
