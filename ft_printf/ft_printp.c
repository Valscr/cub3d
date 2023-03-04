/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vescaffr <vescaffr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:50:41 by vescaffr          #+#    #+#             */
/*   Updated: 2022/05/11 22:52:27 by vescaffr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

#if defined (__APPLE__)
# define PTR_NULL "0x0"
#elif __linux__
# define PTR_NULL "(nil)"
#endif

int	ft_printlen(unsigned long long nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		i++;
		nbr /= 16;
	}
	return (i);
}

void	ft_printpp(unsigned long long nbr)
{
	if (nbr >= 16)
	{
		ft_printpp(nbr / 16);
		ft_printpp(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_printchar(nbr + '0');
		else
			ft_printchar(nbr - 10 + 'a');
	}
	return ;
}

int	ft_printp(unsigned long long nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (count += ft_putstr(PTR_NULL));
	count += write(1, "0x", 2);
	ft_printpp(nbr);
	count += ft_printlen(nbr);
	return (count);
}
