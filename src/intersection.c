/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:45:55 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:59:22 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	inter_0to90(double x, double y, double angle, t_data *game)
{
	double	xlen;
	double	ylen;
	double	size;
	float	tanvalue;
	t_point	p;

	size = 100;
	xlen = size - fmod(x, size);
	ylen = size - fmod(y, size);
	tanvalue = tan(angle * (M_PI / 180));
	if (tanvalue * ylen < (xlen))
	{
		p.x = x + tanvalue * ylen;
		p.y = y + ylen;
		game->nsew = SOUTH;
	}
	else
	{
		p.x = x + xlen;
		tanvalue = tan((45 - (angle - 45)) * (M_PI / 180));
		p.y = y + tanvalue * xlen;
		game->nsew = EAST;
	}
	return (p);
}

t_point	inter_90to180(double x, double y, double angle, t_data *game)
{
	double	xlen;
	double	ylen;
	float	tanvalue;
	t_point	p;

	xlen = 100 - fmod(x, 100);
	if (fmod(y, 100) != 0)
		ylen = fmod(y, 100);
	else if (y == 0)
		ylen = 0;
	else
		ylen = 100;
	tanvalue = tan((angle - 90) * (M_PI / 180));
	if (tanvalue * xlen < (ylen))
	{
		p.x = x + xlen;
		p.y = y - tanvalue * xlen;
		game->nsew = EAST;
		return (p);
	}
	tanvalue = tan((45 - (angle - 135)) * (M_PI / 180));
	p.x = x + tanvalue * ylen;
	p.y = y - ylen;
	game->nsew = NORTH;
	return (p);
}

t_point	inter_180to270(double x, double y, double angle, t_data *game)
{
	double	xlen;
	double	ylen;
	float	tanvalue;
	t_point	p;

	xlen = set_xlen(x);
	ylen = set_ylen(y);
	tanvalue = tan((angle - 180) * (M_PI / 180));
	if (tanvalue * ylen < xlen)
	{
		p.x = x - tanvalue * ylen;
		p.y = y - ylen;
		game->nsew = NORTH;
		return (p);
	}
	tanvalue = tan((45 - (angle - 225)) * (M_PI / 180));
	p.x = x - xlen;
	p.y = y - tanvalue * xlen;
	game->nsew = WEST;
	return (p);
}

t_point	inter_270to360(double x, double y, double angle, t_data *game)
{
	double	xlen;
	double	ylen;
	float	tanvalue;
	t_point	p;

	ylen = 100 - fmod(y, 100);
	if (fmod(x, 100) != 0)
		xlen = fmod(x, 100);
	else if (x == 0)
		xlen = 0;
	else
		xlen = 100;
	tanvalue = tan((angle - 270) * (M_PI / 180));
	if (tanvalue * xlen < ylen)
	{
		p.x = x - xlen;
		p.y = y + tanvalue * xlen;
		game->nsew = WEST;
		return (p);
	}
	tanvalue = tan((45 - (angle - 315)) * (M_PI / 180));
	p.x = x - tanvalue * ylen;
	p.y = y + ylen;
	game->nsew = SOUTH;
	return (p);
}

t_point	intersection(double x, double y, double angle, t_data *game)
{
	t_point	p;

	p.x = 0;
	p.y = 0;
	if (angle == 0 || angle == 180)
		return (inter_0or180(x, y, angle, game));
	else if (angle == 90 || angle == 270)
		return (inter_90or270(x, y, angle, game));
	else if (angle > 0 && angle < 90)
		return (inter_0to90(x, y, angle, game));
	else if (angle > 90 && angle < 180)
		return (inter_90to180(x, y, angle, game));
	else if (angle > 180 && angle < 270)
		return (inter_180to270(x, y, angle, game));
	else if (angle > 270 && angle < 360)
		return (inter_270to360(x, y, angle, game));
	return (p);
}
