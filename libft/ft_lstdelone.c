#include "libft.h"
#include <stdio.h>

void ft_lstdelone(t_list *lst, void (*del)(void*))
{
    if (!lst || !del)
        return;
    del(lst->content);
    free (lst);
}

void    del_content(void *content)
{
    free(content);
}

int main(void)
{
    t_list  *node;
    char    *str;

    str = malloc(20);
    if (!str)
        return (1);
    snprintf(str, 20, "Bonjour");

    node = ft_lstnew(str);
    if (!node)
    {
        free(str);
        return (1);
    }

    printf("Avant ft_lstdelone : %s\n", (char *)node->content);

    ft_lstdelone(node, del_content);

    printf("Apres ft_lstdelone : maillon supprime et memoire liberee\n");

    return (0);
}