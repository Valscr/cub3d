/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 17:13:25 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/20 00:02:26 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putint(int c)
{
	int				i;	
	char			*d;

	d = ft_iitoa(c);
	i = ft_putstr(d);
	free(d);
	return (i);
}

int	ft_putunsigned(unsigned int c)
{
	int				i;
	char			*d;

	d = ft_utoa(c);
	i = ft_putstr(d);
	free(d);
	return (i);
}
