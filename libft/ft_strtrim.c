/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 11:40:59 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/16 09:30:02 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

 
static int	ft_isset(char c, char const *set)
{
	size_t	i;
 
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}
 
static size_t	ft_rmstart(char const *s1, char const *set)
{
	size_t	i;
 
	i = 0;
	while (s1[i] && ft_isset(s1[i], set) == 1)
		i++;
	return (i);
}
 
static size_t	ft_rmend(char const *s1, char const *set)
{
	size_t	cnt;
	size_t	i;
 
	cnt = 0;
	i = ft_strlen(s1);
	while (i > 0 && ft_isset(s1[i - 1], set) == 1)
	{
		cnt++;
		i--;
	}
	return (cnt);
}
 
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	start;
	size_t	end;
 
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	start = ft_rmstart(s1, set);
	if (start == len)
		return (ft_substr(s1, 0, 0));
	end = ft_rmend(s1, set);
	return (ft_substr(s1, start, len - start - end));
}
