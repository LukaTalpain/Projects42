#include <unistd.h>

void ft_putchar_fd(char c, int fd)
{
    write(fd , &c, 1);
}

// int main(void)
// {
//     int fd;

//     fd = open("test.txt", O_WRONLY);
//     ft_putchar_fd('a', fd);
//     return 0;
// }
