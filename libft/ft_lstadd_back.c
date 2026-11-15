#include "libft.h"

void ft_lstadd_back(t_list **lst, t_list *new)
{
    t_list  *ptr;

    ptr = *lst;
    if (ptr == NULL)
        *lst = new;
    else
    {
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new;
    }
}