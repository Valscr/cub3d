/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:50:59 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:57:12 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	set_xlen(double x)
{
	double	xlen;

	xlen = 0;
	if (fmod(x, 100) != 0)
		xlen = fmod(x, 100);
	else if (x == 0)
		xlen = 0;
	else
		xlen = 100;
	return (xlen);
}

double	set_ylen(double y)
{
	double	ylen;

	if (fmod(y, 100) != 0)
		ylen = fmod(y, 100);
	else if (y == 0)
		ylen = 0;
	else
		ylen = 100;
	return (ylen);
}

t_point	endpt_round(double x, double y, double angle, double len)
{
	t_point	point;

	if (angle == 270.0)
	{
		point.x = x - len;
		point.y = y;
	}
	else if (angle == 180.0)
	{
		point.x = x;
		point.y = y - len;
	}
	else if (angle == 90.0)
	{
		point.x = x + len;
		point.y = y;
	}
	else if (angle == 0.0)
	{
		point.x = x;
		point.y = y + len;
	}
	return (point);
}
