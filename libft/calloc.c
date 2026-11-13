#include <stdlib.h>

void *ft_calloc(size_t n, size_t size)
{
    char *ptr = malloc(n * size);
    if (ptr == NULL)
        return (NULL);
    size_t i;

    i = 0;

    while (i < (n * size))
    {
        ptr[i] = '\0';
        i++;
    }
    return ptr;
}

int main(void)
{
#include <stdio.h>
    void *str = ft_calloc(3, sizeof(char));

    printf("%s\n", str);
    free(str);
}