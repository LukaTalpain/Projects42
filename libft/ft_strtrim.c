#include <stdlib.h>

int ft_strlen(char const *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}

char *ft_strtrim(char const *s1, char const *set)
{
    int i;
    int y;
    int x;
    int cnt;

    i = 0;
    y = 0;
    cnt = 0;
    while(s1[i])
    {
        y = 0;
        while (set[y])
        {
            if (s1[i] == set[y])
            {
                cnt++;
            }
            y++;
        }
        i++;
    }
    char    *str = malloc(ft_strlen(s1) - cnt + 1);
    if (str == NULL)
        return (NULL);
    i = 0;
    x = 0;
    while (s1[i])
    {
        cnt = 0;
        y = 0;
        while (set[y])
        {
            if (s1[i] == set[y])
                cnt = 1;
            y++;
        }
        if (cnt == 0)
        {
            str[x] = s1[i];
            x++;
        }
        i++;
    }
    return (str);
}

int main(void)
{
    #include <stdio.h>
    char    *str;
    str = ft_strtrim("Couxcou luvkavx", "x v");
    printf("%s", str);
    free (str);
    return 0;
}
