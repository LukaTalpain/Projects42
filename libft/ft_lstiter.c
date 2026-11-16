#include "libft.h"

void ft_lstiter(t_list *lst, void (*f)(void *))
{
    t_list  *ptr;

    ptr = lst;
    while (ptr->next != NULL)
    {
        f(ptr->content);
        ptr = ptr->next;
    }
}