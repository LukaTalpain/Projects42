/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 09:31:13 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/18 10:03:37 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lstfollow(t_list *lst, void (*del)(void *), t_list *lst2,
		void *(*f)(void *))
{
	t_list			*ptr;
	unsigned int	size;
	t_list			*temp;
	void			*content;

	ptr = lst->next;
	size = ft_lstsize(lst) - 1;
	while (size > 0)
	{
		content = f(ptr->content);
		temp = ft_lstnew(content);
		if (temp == NULL)
		{
			del(content);
			ft_lstclear(&lst2, del);
			return (1);
		}
		ft_lstadd_back(&lst2, temp);
		ptr = ptr->next;
		size--;
	}
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst2;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	content = f(lst->content);
	lst2 = ft_lstnew(content);
	if (lst2 == NULL)
	{
		del(content);
		return (NULL);
	}
	if (ft_lstfollow(lst, del, lst2, f) == 1)
		return (NULL);
	return (lst2);
}
