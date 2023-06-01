/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:22:29 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 19:00:05 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_point	endpt_0to90(double x, double y, double angle, double len)
{
	t_point	point;
	double	angle_rad;

	angle_rad = tan(angle * (M_PI / 180.0));
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
	return (point);
}

t_point	endpt_90to180(double x, double y, double angle, double len)
{
	t_point	point;
	double	angle_rad;

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
	return (point);
}

t_point	endpt_180to270(double x, double y, double angle, double len)
{
	t_point	point;
	double	angle_rad;

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
	return (point);
}

t_point	endpt_270to360(double x, double y, double angle, double len)
{
	t_point	point;
	double	angle_rad;

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
	return (point);
}

t_point	calculate_endpt(double x, double y, double angle, double len)
{
	t_point	point;

	point.x = x;
	point.y = y;
	if (angle == 270.0 || angle == 180.0 || angle == 90.0 || angle == 0.0)
		return (endpt_round(x, y, angle, len));
	else if (angle > 0.0 && angle < 90.0)
		return (endpt_0to90(x, y, angle, len));
	else if (angle > 90.0 && angle < 180.0)
		return (endpt_90to180(x, y, angle, len));
	else if (angle > 180.0 && angle < 270.0)
		return (endpt_180to270(x, y, angle, len));
	else if (angle > 270.0 && angle < 360.0)
		return (endpt_270to360(x, y, angle, len));
	return (point);
}
