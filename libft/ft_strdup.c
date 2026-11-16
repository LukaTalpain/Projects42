/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 10:00:18 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 11:01:40 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s)
{
	char	*str;
	int		s_lenght;
	int		i;

	s_lenght = strlen(s);
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
