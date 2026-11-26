/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 17:14:47 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/26 22:26:05 by ltalpain         ###   ########.fr       */
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


int ft_printf(const char *, ...)
{
    
}


int main(void)
{
    ft_writeint(0);
    return 0;
}
