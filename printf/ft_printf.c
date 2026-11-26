/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:14:47 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/27 00:23:35 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void    ft_recursive(long int n)
{
    if (n >= 1)
    {
        ft_recursive(n / 10);
        n = (n % 10) + '0';
        write (1, &n, 1);
    }
}

void    ft_writestring(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write (1, &str[i], 1);
        i++;
    }
}

void    ft_putchar(char c)
{
    write (1, &c, 1);
}

void    ft_writeint(int n)
{
    long int    nbr;

    nbr = (long int) n;
    if (nbr < 0)
    {
        write(1, "-", 1);
        nbr = nbr * (-1);
    }
    if (nbr == 0)
        write(1, "0", 1);
    ft_recursive(nbr);
}


void    ft_sender(char section, void   *ptr)
{
    if (section == 's')
        ft_writestring((char *) ptr);
    else if (section == 'c')
        ft_putchar((char) ptr);
    else if (section == 'd')
        ft_writeint((int) ptr);
}

int ft_printf(const char *, ...)
{
    
}

#include <stdio.h>
int main(void)
{
    printf ("%s", "coucou");
    ft_writeint(0);
    return 0;
}
