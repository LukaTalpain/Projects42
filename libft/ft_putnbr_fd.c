#include "ft_itoa.c"
#include <unistd.h>
#include <fcntl.h>

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
    
}


void ft_putnbr_fd(int n, int fd)
{
    char    *str;

    str = ft_itoa(n);
    write (fd, str, ft_strlen(str));
    free (str);
}

int main(void)
{
    int fd;

    fd = open("test.txt", O_WRONLY);
    ft_putnbr_fd( 12, fd);
    return 0;
}