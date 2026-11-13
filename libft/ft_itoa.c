#include <stdlib.h>

static int ft_unitcounter(int n)
{
    int cnt;

    cnt = 0;
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

    size = ft_unitcounter(n);
    str = malloc (sizeof(char) * (size + 1));
    if (str == NULL)
        return (NULL);
    str[size] = '\0';
    if (n < 0)
    {
        str[0] = '-';
        n = n * (-1);
    }
    size--;
    while (n >= 1 )
    {
        str[size] = (n % 10) + '0';
        n = n/10;
        size--;
    }
    return(str);
}

int main(void)
{
    #include <stdio.h>
    char    *str;

    str = ft_itoa(-5232);
    printf("%s\n", "resultat  :");
    printf("%s", str);
    free (str);
    return 0;
}
