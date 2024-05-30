/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschlott <rschlott@student.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 15:56:37 by rschlott          #+#    #+#             */
/*   Updated: 2023/02/02 12:09:36 by rschlott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
//#include <stdlib.h>
#include <stdarg.h>

int	ft_print_string(char *str)
{
	int	i;

	i = -1;
	if (!str)
		str = "(null)";
	while (str[++i])
		write(1, &str[i], 1);
	return (i);
}

int	ft_put_digit(long long int number, int base)
{
	char	*hexadecimal;
	int		length;

	hexadecimal = "0123456789abcdef";
	length = 0;
	if (number < 0)
	{
		number *= -1;
		length += write(1, "-", 1);
	}
	if (number >= base)
		length += ft_put_digit(number / base, base);
	length += write(1, &hexadecimal[number % base], 1);
	return (length);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		length;
	va_list	args;

	va_start(args, format);
	i = -1;
	length = 0;
	while (format[++i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			if (format[i] == 's')
				length += ft_print_string(va_arg(args, char *));
			else if (format[i] == 'd')
				length += ft_put_digit((long long int)va_arg(args, int), 10);
			else if (format[i] == 'x')
				length += ft_put_digit((long long int)va_arg(args,
							unsigned int), 16);
			else if (format[i] == '%')
				length += write(1, &format[i], 1);
		}
		else
			length += write(1, &format[i], 1);
	}
	va_end(args);
	return (length);
}

/*int main()
{
	int i;
	int p;
	char *str = "hello";

	i = 0;
	p = 0;
	i = ft_printf("my:%d %d %d %d \n", -2147483647, 0, 40 ,-23);
	p = printf("th:%d %d %d %d \n", -2147483647, 0, 40 ,-23);
	ft_printf ("my length: %d\n their length: %d\n", i, p);

	i = ft_printf("my:%x %x %x %x \n", -2147483647, 0, 40 ,-23);
	p = printf("th:%x %x %x %x \n", -2147483647, 0, 40 ,-23);
	ft_printf ("my length: %d\n their length: %d\n", i, p);

	i = ft_printf("the word %s is cool\n",str);
	p = printf("the word %s is cool\n", str);
	ft_printf ("my length: %d\n their length: %d\n", i, p);

	return (0);
}*/
