#include <stdlib.h>

static int ft_unitcounter(long int n)
{
    int cnt;

    cnt = 0;
    if (n == 0)
        return (1);
    if (n < 0)
    {
        cnt++;
        n = n * (-1);
    }
    while (n >= 1)
    {
        n = n/10;
        cnt++;
    }
    return (cnt);
}

char *ft_itoa(int n)
{
    char    *str;
    int size;
    long int    nb;

    nb = n;
    size = ft_unitcounter(nb);
    str = malloc (sizeof(char) * (size + 1));
    if (str == NULL)
        return (NULL);
    str[size] = '\0';
    if (nb == 0)
    {
        str[0] = '0';
        return (str);
    }
    if (nb < 0)
    {
        str[0] = '-';
        nb = nb * (-1);
    }
    size--;
    while (nb >= 1 )
    {
        str[size] = (nb % 10) + '0';
        nb = nb/10;
        size--;
    }
    return(str);
}

// int main(void)
// {
//     #include <stdio.h>
//     char    *str;

//     str = ft_itoa(-5232);
//     printf("%s\n", "resultat  :");
//     printf("%s", str);
//     free (str);
//     return 0;
// }
