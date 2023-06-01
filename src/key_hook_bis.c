/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 18:38:08 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 19:42:18 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	move_forward(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->forward)
	{
		angle = game->angle;
		point = calculate_endpt(game->posx, game->posy, angle, SPEED_F_B);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	return ;
}

void	move_backward(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->back)
	{
		if (game->angle < 180.0)
			angle = game->angle + 180.0;
		else
			angle = game->angle - 180.0;
		point = calculate_endpt(game->posx, game->posy, angle, SPEED_F_B);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	return ;
}

void	move_left(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->left)
	{
		if (game->angle >= 270.0)
			angle = game->angle - 270.0;
		else
			angle = game->angle + 90.0;
		point = calculate_endpt(game->posx, game->posy, angle, SPEED_L_R);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	return ;
}

void	move_right(t_data *game)
{
	double	angle;
	t_point	point;

	if (game->right)
	{
		if (game->angle < 90.0)
			angle = game->angle + 270.0;
		else
			angle = game->angle - 90.0;
		point = calculate_endpt(game->posx, game->posy, angle, SPEED_L_R);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
		}
	}
	return ;
}

void	rotate(t_data *game)
{
	if (game->rotate_left)
	{
		if (game->angle >= 360 - SPEED_ROTATE)
			game->angle = 0.0;
		else
			game->angle += SPEED_ROTATE;
	}
	else if (game->rotate_right)
	{
		if (game->angle < SPEED_ROTATE - 1)
			game->angle = 359.0;
		else
			game->angle -= SPEED_ROTATE;
	}
	return ;
}
