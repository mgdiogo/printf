/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpedroso <mpedroso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:19:33 by mpedroso          #+#    #+#             */
/*   Updated: 2022/11/14 17:14:12 by mpedroso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putstr(const char *s)
{
	int	i;

	if (!s)
		return (ft_putstr("(null)"));
	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}

static int	ft_putnbr_p(unsigned long long n, char *base, int j, int fe)
{
	int	i;

	i = 0;
	if (!n && fe == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	if (fe == 0)
	{
		ft_putstr("0x");
		i += 2;
	}
	if (n / j > 0)
		i += ft_putnbr_p(n / j, base, j, 1);
	write (1, &base[n % j], 1);
	i++;
	return (i);
}

static int	ft_putnbr_base(long long int n, char *base, int j)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		write (1, "-", 1);
		n = -n;
		i++;
	}
	if (n / j > 0)
		i += ft_putnbr_base(n / j, base, j);
	write (1, &base[n % j], 1);
	i++;
	return (i);
}

static int	format(char s, va_list args)
{
	int	i;
	int	k;

	i = 1;
	if (s == 'c')
	{
		k = va_arg(args, int);
		write (1, &k, 1);
	}	
	else if (s == 's')
		i = ft_putstr(va_arg(args, char *));
	else if (s == '%')
		write (1, "%%", 1);
	else if (s == 'i' || s == 'd')
		i = ft_putnbr_base(va_arg(args, int), "0123456789", 10);
	else if (s == 'u')
		i = ft_putnbr_base(va_arg(args, unsigned int), "0123456789", 10);
	else if (s == 'x')
		i = ft_putnbr_base(va_arg(args, unsigned int), "0123456789abcdef", 16);
	else if (s == 'X')
		i = ft_putnbr_base(va_arg(args, unsigned int), "0123456789ABCDEF", 16);
	else if (s == 'p')
		i = ft_putnbr_p(va_arg(args, long int), "0123456789abcdef", 16, 0);
	return (i);
}

int	ft_printf(const char *s, ...)
{
	va_list	args;
	int		i;
	int		printedc;

	va_start(args, s);
	i = 0;
	printedc = 0;
	while (*s)
	{
		if (*s != '%')
		{
			write (1, &*s, 1);
			printedc++;
		}
		else
		{
			s++;
			printedc += format(*s, args);
		}
		s++;
	}
	va_end(args);
	return (printedc);
}
