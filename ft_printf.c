/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:19:33 by mpedroso          #+#    #+#             */
/*   Updated: 2022/11/10 17:09:42 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

static int	ft_putstr(const char *s)
{
	int	i;

	if (!s)
		return (ft_putstr("(null)"));
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
	return (i);
}

static int	ft_putchar(const char s)
{
	write (1, &s, 1);
	return (1);
}

static int	ft_putnbr_base(long long int n, char *base, int j)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		ft_putstr('-');
		n = -n;
		i++;
	}
	if (n / j > 0)
		i += ft_putnbr_base(n / j, base, j);
	ft_putchar(base[n % j]);
	return (i);
}

static int	ft_print(char s, va_list args)
{
	int	i;

	i = 0;
	if (s == 'c')
		ft_putchar(va_arg(args, int));
	if (s == 's')
		i = ft_putstr(va_arg(args, char *));
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		printedc;

	va_start(args, s);
	i = 0;
	printedc = 0;
	while (s[i])
	{
		if (s[i] != '%')
		{
			ft_putstr(s);
			printedc++;
		}
		else
		{
			
		}
		i++;
	}
	return (printedc);
}
