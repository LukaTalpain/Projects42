#include "libft.h"

t_list *ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
    t_list  *lst2;
    t_list  *ptr;
    t_list  *temp;
    void    *content;
    unsigned int    size;

    if (!lst || !f || !del)
        return NULL;
    content = f(lst->content);
    lst2 = ft_lstnew(content);
    if (lst2 == NULL)
    {
        del(content);
        return (NULL);
    }
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
            return (NULL);
        }
        ft_lstadd_back(&lst2, temp);
        ptr = ptr->next;
        size--;
    }
     return (lst2);   
}


