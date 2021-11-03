/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhaddi <mhaddi@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:36:35 by mhaddi            #+#    #+#             */
/*   Updated: 2021/09/29 12:11:25 by mhaddi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>

int count_chars;

void ft_putnbr(int n)
{
	unsigned int nb;
	char c;

	if (n < 0)
	{
		write(1, "-", 1);
		count_chars++;
		nb = -n;
	}
	else
		nb = n;

	if (nb >= 10)
	{
		ft_putnbr(nb / 10);
		ft_putnbr(nb % 10);
	}
	else
	{
		c = '0' + nb;
		write(1, &c, 1);
		count_chars++;
	}
}

void ft_putnbr_hex(unsigned int x)
{
	char *hex_digits = "0123456789abcdef";

	if (x >= 16)
	{
		ft_putnbr_hex(x / 16);
		ft_putnbr_hex(x % 16);
	}
	else
	{
		write(1, &hex_digits[x], 1);
		count_chars++;
	}
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	
	return i;
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int i;
	int d;
	unsigned int x;
	char *str;

	va_start(ap, fmt);

	i = 0;	
	count_chars = 0;
	while (fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			while (fmt[i] == ' ' || fmt[i] == '\t')
				i++;
			if (fmt[i] == 'd')
			{
				d = va_arg(ap, int);
				ft_putnbr(d);
			}
			else if (fmt[i] == 'x')
			{
				x = va_arg(ap, unsigned int);
				ft_putnbr_hex(x);
			}
			else if (fmt[i] == 's')
			{
				str = va_arg(ap, char *);
				if (str != NULL)
				{
					write(1, str, ft_strlen(str));
					count_chars += ft_strlen(str);
				}
				else
				{
					write(1, "(null)", ft_strlen("(null)"));
					count_chars += ft_strlen("(null)");
				}
			}
			else
			{
				write(1, &fmt[i], 1);
				count_chars++;
			}
		}
		else
		{
			write(1, &fmt[i], 1);
			count_chars++;
		}
		i++;
	}

	va_end(ap);

	return count_chars;
}
