/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 09:55:00 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/24 11:19:20 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	n;

	n = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			n++;
		while (*s && *s != c)
			s++;
	}
	return (n);
}

static char	*dup_word(const char *s, size_t len)
{
	char	*w;
	size_t	i;

	w = malloc(len + 1);
	if (!w)
		return (NULL);
	i = 0;
	while (i < len)
	{
		w[i] = s[i];
		i++;
	}
	w[i] = '\0';
	return (w);
}

static int	fill(char **tab, const char *s, char c, size_t words)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (i < words)
	{
		while (*s == c)
			s++;
		len = 0;
		while (s[len] && s[len] != c)
			len++;
		tab[i] = dup_word(s, len);
		if (!tab[i])
		{
			while (i > 0)
				free(tab[--i]);
			return (0);
		}
		s += len;
		i++;
	}
	tab[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (!fill(tab, s, c, words))
	{
		free(tab);
		return (NULL);
	}
	return (tab);
}
