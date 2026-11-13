#include <stdlib.h>

int ft_strlen(const char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
}

char    ft_test(unsigned int i, char c)
{
    if (i > 0 && c == 'a')
        return ('B');
    return (c);
}

char *ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
    int size;
    char    *str;
    unsigned int i;

    size = ft_strlen(s);
    str = malloc(sizeof(char) * size);
    i = 0;
    while (s[i])
    {
        str[i] = f(i, s[i]);
        i++;
    }
    str[i] = '\0';
    return (str);
}

int main(void)
{
    #include <stdio.h>
    char    *str;

    str = ft_strmapi("ae suis a", ft_test);
    printf("%s", str);
    free (str);
    return 0;
}
