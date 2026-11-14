#include <unistd.h>
#include <fcntl.h>

void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

int main(void)
{
    int fd;

    fd = open("test.txt", O_WRONLY);
    ft_putchar_fd('b', fd);
    return 0;
}
