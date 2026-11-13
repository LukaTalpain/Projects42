void    ft_test(unsigned int i, char *c)
{
    if (i == 0)
    {
        c[i] = 'L';
    }
}

void ft_striteri(char *s, void (*f)(unsigned int,char*))
{
    unsigned int i;

    i = 0;
    while (s[i])
    {
        f(i, s);
        i++;
    }
}

int main(void)
{
    #include <stdio.h>
    char    str[] = "Yuka";

    ft_striteri(str, ft_test);
    printf("%s", str);
    return 0;
}
