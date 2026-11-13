#include <stdlib.h>

int ft_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strjoin(char const *s1, char const *s2)
{
    char    *str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (str == NULL)
        return (NULL);
    int i;
    int y;

    i = 0;
    y = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while (s2[y])
    {
        str[i] = s2[y];
        i++;
        y++;
    }
    return (str);
    
}

int main(void)
{
    #include <stdio.h>
    char    *str;

    str = ft_strjoin("coucou je m'appelle ", "Luka");
    printf("%s\n", str);
    free (str);
    return 0;
}
