#include "libft.h"

unsigned int ft_lstsize(t_list *lst)
{
    unsigned int    i;
    t_list  *ptr;

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


// int main(void)
// {
//     t_list *lst;

//     lst = NULL;

//     printf("Taille initiale : %u\n", ft_lstsize(lst));

//     ft_lstadd_front(&lst, ft_lstnew("Troisieme"));
//     ft_lstadd_front(&lst, ft_lstnew("Deuxieme"));
//     ft_lstadd_front(&lst, ft_lstnew("Premier"));

//     printf("Taille de la liste : %u\n", ft_lstsize(lst));

//     return (0);
// }