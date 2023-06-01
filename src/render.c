/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:19:33 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 22:55:58 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

void	render_background(t_img *img, t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, game->color_ceiling);
		}
		++i;
	}
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, game->color_floor);
		}
		++i;
	}
}

int	render(t_data *game)
{	
	int			i;
	double		angle;
	t_point		p;
	t_pointt	point;

	i = WINDOW_WIDTH;
	if (game->angle < 45)
		angle = 360.0 - (45.0 - game->angle);
	else
		angle = game->angle - 45.0;
	while (--i >= 0)
	{
		p.x = game->posx;
		p.y = game->posy;
		while (!check_wall(p.x, p.y, game))
			p = intersection(p.x, p.y, angle, game);
		point.x[i] = p.x;
		point.y[i] = p.y;
		game->orient[i] = game->nsew;
		if (angle >= 360 - 90.0 / (double)WINDOW_WIDTH)
			angle = 0;
		else
			angle += 90.0 / (double)WINDOW_WIDTH;
	}
	return (loop_render_rect(WINDOW_WIDTH - 1, point, game), 0);
}

int	render_next_frame(t_data *game)
{
	render_background(&game->img, game);
	render(game);
	render_sight(&game->img);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.mlx_img, 0, 0);
	move_forward(game);
	move_left(game);
	move_right(game);
	move_backward(game);
	rotate(game);
	return (0);
}
