/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:22:29 by valentin          #+#    #+#             */
/*   Updated: 2023/05/30 13:23:18 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point intersection(double x, double y, double angle, t_data *game)
{
	t_point	p;
	float	tanValue = tan(angle * (M_PI / 180));

	p.x = 0;
	p.y = 0;
	double xlen = 0;
	double ylen = 0;
	double size = 100;
	if (angle == 0)
	{
		p.x = x;
		p.y = y + (size - fmod(y, size));
		game->color = RED_PIXEL;
	}
	else if (angle == 180)
	{
		if (fmod(y, size) != 0)
			ylen = fmod(y, size);
		else if (y == 0)
			ylen = 0;
		else
			ylen = size;
		p.x = x;
		p.y = y - (ylen);
		game->color = BLUEDARK_PIXEL;
	}
	else if (angle == 90)
	{
		p.x = x + (size - fmod(x, size));
		p.y = y;
		game->color = REDDARK_PIXEL;
	}
	else if (angle == 270)
	{
		if (fmod(x, size) != 0)
			xlen = fmod(x, size);
		else if (x == 0)
			xlen = 0;
		else
			xlen = size;
		p.x = x - (xlen);
		p.y = y;
		game->color = BLUE_PIXEL;
	}
	else if (angle > 0 && angle < 90)
	{
		xlen = size - fmod(x, size);
		ylen = size - fmod(y, size);
		if (tanValue * ylen < (xlen))
		{
			p.x = x + tanValue * ylen;
			p.y = y + ylen;
			game->color = RED_PIXEL;
		}
		else
		{
			p.x = x + xlen;
			tanValue = tan((45 - (angle - 45)) * (M_PI / 180));
			p.y = y + tanValue * xlen;
			game->color = REDDARK_PIXEL;
		}
	}
	else if (angle > 90 && angle < 180)
	{
		xlen = size - fmod(x, size);
		if (fmod(y, size) != 0)
			ylen = fmod(y, size);
		else if (y == 0)
			ylen = 0;
		else
			ylen = size;
		tanValue = tan((angle - 90) * (M_PI / 180));
		if (tanValue * xlen < (ylen))
		{
			p.x = x + xlen;
			p.y = y - tanValue * xlen;
			game->color = REDDARK_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 135)) * (M_PI / 180));
			p.x = x + tanValue * ylen;
			p.y = y - ylen;
			game->color = BLUEDARK_PIXEL;
		}
	}
	else if (angle > 180 && angle < 270)
	{
		if (fmod(x, size) != 0)
			xlen = fmod(x, size);
		else if (x == 0)
			xlen = 0;
		else
			xlen = size;
		if (fmod(y, size) != 0)
			ylen = fmod(y, size);
		else if (y == 0)
			ylen = 0;
		else
			ylen = size;
		tanValue = tan((angle - 180) * (M_PI / 180));
		if (tanValue * ylen < xlen)
		{
			p.x = x - tanValue * ylen;
			p.y = y - ylen;
			game->color = BLUEDARK_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 225)) * (M_PI / 180));
			p.x = x - xlen;
			p.y = y - tanValue * xlen;
			game->color = BLUE_PIXEL;
		}
	}
	else if (angle > 270 && angle < 360)
	{
		ylen = size - fmod(y, size);
		if (fmod(x, size) != 0)
			xlen = fmod(x, size);
		else if (x == 0)
			xlen = 0;
		else
			xlen = size;
		tanValue = tan((angle - 270) * (M_PI / 180));
		if (tanValue * xlen < ylen)
		{
			p.x = x - xlen;
			p.y = y + tanValue * xlen;
			game->color = BLUE_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 315)) * (M_PI / 180));
			p.x = x - tanValue * ylen;
			p.y = y + ylen;
			game->color = RED_PIXEL;
		}
	}
	return (p);
}

t_point calculate_endpoint(double x, double y, double angle, double len)
{
    t_point point;

    double angle_rad =  tan(angle * (M_PI / 180.0));
	point.x = x;
	point.y = y;
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
	else if (angle > 0.0 && angle < 90.0)
	{
		if (angle <= 45.0)
		{
			point.x = x + len * sin(angle_rad);
    		point.y = y + len * cos(angle_rad);
		}
		else
		{
			angle_rad = tan(((90.0 - angle)) * (M_PI / 180.0));
			point.x = x + len * cos(angle_rad);
    		point.y = y + len * sin(angle_rad);
		}
	}
	else if (angle > 90.0 && angle < 180.0)
	{
		angle_rad = tan((angle - 90.0) * (M_PI / 180.0));
		if (angle <= 135.0)
		{
			point.x = x + len * cos(angle_rad);
    		point.y = y - len * sin(angle_rad);
		}
		else
		{
			angle_rad = tan((90.0 - (angle - 90.0)) * (M_PI / 180.0));
			point.x = x + len * sin(angle_rad);
    		point.y = y - len * cos(angle_rad);
		}
	}
	else if (angle > 180.0 && angle < 270.0)
	{
		angle_rad = tan((angle - 180.0) * (M_PI / 180.0));
		if (angle <= 225.0)
		{
			point.x = x - len * sin(angle_rad);
    		point.y = y - len * cos(angle_rad);
		}
		else
		{
			angle_rad = tan((90.0 - (angle - 180.0)) * (M_PI / 180.0));
			point.x = x - len * cos(angle_rad);
    		point.y = y - len * sin(angle_rad);
		}
	}
	else if (angle > 270.0 && angle < 360.0)
	{
		angle_rad = tan((angle - 270.0) * (M_PI / 180.0));
		if (angle <= 315.0)
		{
			point.x = x - len * cos(angle_rad);
    		point.y = y + len * sin(angle_rad);
		}
		else
		{
			angle_rad = tan((90.0 - (angle - 270.0)) * (M_PI / 180.0));
			point.x = x - len * sin(angle_rad);
    		point.y = y + len * cos(angle_rad);
		}
	}
    return point;
}