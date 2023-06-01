/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_rect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:30:55 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 16:32:16 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	get_pixel(t_data *game, int x, int y, int orient)
{
	unsigned int	*pixel_ptr;

	pixel_ptr = (unsigned int *)(game->texture[orient].addr
			+ (y * game->texture[orient].line_len)
			+ (x * (game->texture[orient].bpp / 8)));
	return (*pixel_ptr);
}

int	render_rect_bis(t_rect rect, double start, t_data *game, int d)
{
	double				i;
	double				j;
	int					recty;

	recty = rect.y;
	i = 0;
	if (rect.height > WINDOW_HEIGHT)
		rect.height = WINDOW_HEIGHT;
	if (rect.y < 0)
		recty = 0;
	else
		i = rect.y;
	while (i < recty + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			img_pix_put(&game->img, j, i, get_pixel(game, ((j - rect.x)
						* game->scale_x) + (start * game->scale_x),
					((i - rect.y) * game->scale_y), game->orient[d]));
			j++;
		}
		++i;
	}
	return (0);
}

int	loop_render_rect(int i, t_pointt point, t_data *game)
{
	double	d;

	d = 0.0;
	while (i >= 0)
	{
		d = distance(game->posx, game->posy, point.x[i], point.y[i]);
		render_rect((t_rect){i, ((double)WINDOW_HEIGHT / 2.0)
			- ((((double)WINDOW_HEIGHT / d) * 100.0) / 2.0), 1,
			((double)WINDOW_HEIGHT / d) * 100.0, game->nsew}, game, point, i);
		i--;
	}
	return (0);
}

int	render_rect(t_rect rect, t_data *game, t_pointt point, int d)
{
	double	start;

	start = 0;
	if (game->orient[d] == NORTH)
		start = fmod(point.x[d], 100);
	else if (game->orient[d] == SOUTH)
		start = fmod(point.x[d], 100);
	else if (game->orient[d] == WEST)
		start = fmod(point.y[d], 100);
	else if (game->orient[d] == EAST)
		start = fmod(point.y[d], 100);
	game->scale_x = (float)game->texture[game->orient[d]].width / 100.0;
	game->scale_y = (float)game->texture[game->orient[d]].height
		/ (rect.height);
	render_rect_bis(rect, start, game, d);
	return (0);
}
