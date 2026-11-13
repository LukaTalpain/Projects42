#include <stdlib.h>

char *ft_substr(char const *s, unsigned int start, size_t len)
{
    int size;
    int i;

    size = len - start;
    i = 0;
    char *str = malloc(size + 1);
    if (str == NULL)
        return (NULL);
    if (s == NULL)
        return (NULL);
    while (start <= len)
    {
        str[i] = s[start];
        start++;
        i++;
    }
    return (str);    
}

int main(void)
{
    #include <stdio.h>
    char *str = ft_substr("Hello, World!", 7, 12);
    printf("%s\n", str);
    free(str);
}
