#include <string.h>
#include <stdlib.h>
char *strdup(const char *s)
{
    int s_lenght;

    s_lenght = strlen(s);
    char *str = malloc(s_lenght + 1);
    if (str == NULL)
        return (NULL);
    int i = 0;
    while (i < s_lenght)
    {
        str[i] = s[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

int main(void)
{
#include <stdio.h>
    char *str = strdup("Hello, World!");
    printf("%s\n", str);
    free(str);
}