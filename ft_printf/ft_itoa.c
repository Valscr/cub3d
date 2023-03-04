/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:23:46 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/20 00:00:19 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_ppow(int nb, int power)
{
	int	i;
	int	res;

	if (power < 0)
		return (0);
	i = 0;
	res = 1;
	while (i++ < power)
		res *= nb;
	return (res);
}

int	ft_ddestsize(int n)
{
	unsigned int	nb;
	int				size;

	size = 1;
	if (n < 0)
	{
		size++;
		nb = (unsigned int)(n * -1);
	}
	else
		nb = (unsigned int)n;
	while (nb >= 10)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_ffilldest(unsigned int nb, char *dest, int i, int size)
{
	while (size > 0)
	{
		dest[i++] = nb / ft_ppow(10, size) + '0';
		nb = nb - (nb / ft_ppow(10, size) * ft_ppow(10, size));
		size--;
	}
	dest[i] = nb + '0';
	dest[++i] = '\0';
	return (dest);
}

char	*ft_iitoa(int n)
{
	char			*dest;
	unsigned int	nb;
	int				size;
	int				i;

	i = 0;
	size = ft_ddestsize(n);
	dest = malloc(sizeof(char) * (size-- + 1));
	if (!dest)
		return (0);
	if (n < 0)
	{
		dest[i++] = '-';
		size--;
		nb = (unsigned int)(n * -1);
	}
	else
		nb = (unsigned int)n;
	dest = ft_ffilldest(nb, dest, i, size);
	return (dest);
}
