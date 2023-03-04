/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 00:06:02 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/20 00:02:06 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "ft_printf.h"

int			ft_printf(const char *in, ...);
int			ft_putstr(const char *c);
int			ft_printlen(unsigned long long nbr);
int			ft_printcounthex(unsigned int a);
int			ft_printhex(unsigned int a, const char in);
void		ft_printpp(unsigned long long nbr);
int			ft_printp(unsigned long long nbr);
int			ft_putint(int c);
int			ft_putunsigned(unsigned int c);
int			ft_printchar(int c);
int			ft_ppow(int nb, int power);
int			ft_ddestsize(int n);
char		*ft_ffilldest(unsigned int nb, char *dest, int i, int size);
char		*ft_iitoa(int n);
int			ft_udestsize(unsigned int n);
char		*ft_utoa(unsigned int n);

#endif
