/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:30:29 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/18 09:30:29 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_lstsize(t_list *lst)
{
	unsigned int	i;
	t_list			*ptr;

	i = 1;
	ptr = lst;
	if (ptr == NULL)
		return (0);
	while (ptr->next != NULL)
	{
		i++;
		ptr = ptr->next;
	}
	return (i);
}
