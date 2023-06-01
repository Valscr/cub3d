/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:49:10 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:57:27 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	inter_0or180(double x, double y, double angle, t_data *game)
{
	t_point	p;
	double	ylen;

	ylen = 0;
	if (angle == 0)
	{
		p.x = x;
		p.y = y + (100 - fmod(y, 100));
		game->nsew = SOUTH;
	}
	else if (angle == 180)
	{
		if (fmod(y, 100) != 0)
			ylen = fmod(y, 100);
		else if (y == 0)
			ylen = 0;
		else
			ylen = 100;
		p.x = x;
		p.y = y - (ylen);
		game->nsew = NORTH;
	}
	return (p);
}

t_point	inter_90or270(double x, double y, double angle, t_data *game)
{
	t_point	p;
	double	xlen;

	xlen = 0;
	if (angle == 90)
	{
		p.x = x + (100 - fmod(x, 100));
		p.y = y;
		game->nsew = EAST;
	}
	else if (angle == 270)
	{
		if (fmod(x, 100) != 0)
			xlen = fmod(x, 100);
		else if (x == 0)
			xlen = 0;
		else
			xlen = 100;
		p.x = x - (xlen);
		p.y = y;
		game->nsew = WEST;
	}
	return (p);
}
