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

void ft_putstr_fd(char *s, int fd)
{
    write (fd, s, ft_strlen(s));
}


int main(void)
{
    int fd;

    fd = open("test.txt", O_WRONLY);
    ft_putstr_fd("Bonjour", fd);
    return 0;
}