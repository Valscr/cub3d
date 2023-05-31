/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:35 by valentin          #+#    #+#             */
/*   Updated: 2023/05/31 16:33:33 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	mykey_hook(int keycode, t_data *game)
{	
	t_point point;
	double angle;

	angle = game->angle;
	if (keycode == XK_Escape)
		end(game);
	else if (keycode == XK_Up)
	{
		angle = game->angle;
		point = calculate_endpoint(game->posx, game->posy, angle, 8);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	else if (keycode == XK_Left)
	{
		if (game->angle >= 270.0)
			angle = game->angle - 270.0;
		else
			angle = game->angle + 90.0;
		point = calculate_endpoint(game->posx, game->posy, angle, 4);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	else if (keycode == XK_Right)
	{
		if (game->angle < 90.0)
			angle = game->angle + 270.0;
		else
			angle = game->angle - 90.0;
		point = calculate_endpoint(game->posx, game->posy, angle, 4);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	else if (keycode == XK_Down)
	{
		if (game->angle < 180.0)
			angle = game->angle + 180.0;
		else
			angle = game->angle - 180.0;
		point = calculate_endpoint(game->posx, game->posy, angle, 8);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	else if (keycode == XK_r)
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
	return (0);
}