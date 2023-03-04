/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:35:10 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/20 00:39:28 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_udestsize(unsigned int n)
{
	unsigned int	nb;
	int				size;

	size = 1;
	nb = (unsigned int)n;
	while (nb >= 10)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_utoa(unsigned int n)
{
	char			*dest;
	unsigned int	nb;
	int				size;
	int				i;

	i = 0;
	size = ft_udestsize(n);
	dest = malloc(sizeof(char) * (size-- + 1));
	if (!dest)
		return (0);
	nb = (unsigned int)n;
	dest = ft_ffilldest(nb, dest, i, size);
	return (dest);
}
