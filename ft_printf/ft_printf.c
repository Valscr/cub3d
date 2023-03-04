/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 14:41:11 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/20 00:02:10 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printfbis(va_list ap, const char in)
{
	int	car;

	car = 0;
	if (in == 's')
		car += ft_putstr(va_arg(ap, const char *));
	else if (in == 'c')
		car += ft_printchar(va_arg(ap, int));
	else if (in == 'd' || in == 'i')
		car += ft_putint(va_arg(ap, int));
	else if (in == '%')
		car += ft_printchar('%');
	else if (in == 'u')
		car += ft_putunsigned(va_arg(ap, unsigned int));
	else if (in == 'p')
		car += ft_printp(va_arg(ap, unsigned long long));
	else if (in == 'x' || in == 'X')
		car += ft_printhex(va_arg(ap, unsigned int), in);
	return (car);
}

int	ft_printf(const char *in, ...)
{
	va_list			ap;
	int				i;
	int				count;

	count = 0;
	i = 0;
	va_start(ap, in);
	while (in[i] != '\0')
	{
		if (in[i] == '%')
			count += ft_printfbis(ap, in[++i]);
		else
			count += ft_printchar(in[i]);
		i++;
	}
	va_end(ap);
	return (count);
}

/*int	main()
{	
	char    *d;

	d = "%s";
	ft_printf(d, NULL);
	printf("\n");
	printf(d, NULL);
	printf("\n");
	printf("longeur de printf = %d\n", printf(d, NULL));
	printf("longeur de ft_printf = %d\n", ft_printf(d, NULL));
}*/
