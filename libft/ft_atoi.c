/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltalpain <ltalpain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 09:57:58 by ltalpain          #+#    #+#             */
/*   Updated: 2026/11/12 10:17:37 by ltalpain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *arg)
{
	int				i;
	unsigned int	nb;
	int				negative;

	i = 0;
	negative = 0;
	nb = 0;
	while (arg[i] == ' ' || (arg[i] >= '\a' && arg[i] <= '\r'))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			negative = 1;
		i++;
	}
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		nb = (nb * 10) + arg[i] - '0';
		i++;
	}
	if (negative == 1)
		nb = nb * (-1);
	return (nb);
}

// #include <stdio.h>
// #include <stdlib.h>

// static int	g_fail = 0;

// static void	test(const char *str)
// {
// 	int	mine;
// 	int	ref;

// 	mine = ft_atoi(str);
// 	ref = atoi(str);
// 	printf("[%s] \"%s\" -> ft_atoi=%d atoi=%d\n", mine == ref ? "OK" : "KO",
// 		str, mine, ref);
// 	if (mine != ref)
// 		g_fail++;
// }

// int	main(void)
// {
// 	test("42");
// 	test("0");
// 	test("-42");
// 	test("+42");
// 	test("   42");
// 	test("\t\n\v\f\r 42");
// 	test("42abc");
// 	test("abc42");
// 	test("");
// 	test("   ");
// 	test("-");
// 	test("+");
// 	test("--42");
// 	test("+-42");
// 	test("-+42");
// 	test("- 42");
// 	test("0042");
// 	test("-0");
// 	test("2147483647");
// 	test("-2147483648");
// 	test("12 34");

// 	printf("\n%s\n",
// 		g_fail ? "Des tests ont échoué" : "Tous les tests passent");
// 	return (g_fail != 0);
// }