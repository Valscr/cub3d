/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 17:35:32 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/11 18:03:51 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printcounthex(unsigned int a)
{
	int	i;

	i = 0;
	while (a != 0)
	{
		i++;
		a /= 16;
	}
	return (i);
}

int	ft_printhex(unsigned int a, const char in)
{
	if (a == 0)
		return (write(1, "0", 1));
	if (a >= 16)
	{
		ft_printhex((a / 16), in);
		ft_printhex((a % 16), in);
	}
	else
	{
		if (a <= 9)
			ft_printchar(a + '0');
		else if (in == 'x')
			ft_printchar(a - 10 + 'a');
		else if (in == 'X')
			ft_printchar(a - 10 + 'A');
	}
	return (ft_printcounthex(a));
}
