/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:38:08 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:59:20 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *game)
{
	double	angle;
	t_point	point;

	angle = game->angle;
	point = calculate_endpt(game->posx, game->posy, angle, 8);
	if (!check_wall(point.x, point.y, game))
	{
		game->posy = point.y;
		game->posx = point.x;
	}
	return ;
}

void	move_backward(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->angle < 180.0)
		angle = game->angle + 180.0;
	else
		angle = game->angle - 180.0;
	point = calculate_endpt(game->posx, game->posy, angle, 8);
	if (!check_wall(point.x, point.y, game))
	{
		game->posy = point.y;
		game->posx = point.x;
	}
	return ;
}

void	move_left(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->angle >= 270.0)
		angle = game->angle - 270.0;
	else
		angle = game->angle + 90.0;
	point = calculate_endpt(game->posx, game->posy, angle, 4);
	if (!check_wall(point.x, point.y, game))
	{
		game->posy = point.y;
		game->posx = point.x;
	}
	return ;
}

void	move_right(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->angle < 90.0)
		angle = game->angle + 270.0;
	else
		angle = game->angle - 90.0;
	point = calculate_endpt(game->posx, game->posy, angle, 4);
	if (!check_wall(point.x, point.y, game))
	{
		game->posy = point.y;
		game->posx = point.x;
	}
	return ;
}

void	rotate(t_data *game, int keycode)
{
	if (keycode == XK_r)
	{
		if (game->angle >= 358.0)
			game->angle = 0.0;
		else
			game->angle += 2.0;
	}
	else if (keycode == XK_t)
	{
		if (game->angle < 1.0)
			game->angle = 359.0;
		else
			game->angle -= 2.0;
	}
	return ;
}
