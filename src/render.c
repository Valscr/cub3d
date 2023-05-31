/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:19:33 by valentin          #+#    #+#             */
/*   Updated: 2023/05/31 16:19:45 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
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

unsigned int get_pixel(char *addr, int x, int y, int line_len, int bpp)
{
	unsigned int *pixel_ptr = (unsigned int *)(addr + (y * line_len) + (x * (bpp / 8)));
	return *pixel_ptr;
}


int render_rect(t_rect rect, t_data *game, t_pointt point, int d)
{
	double	i;
	double j;
	double start;
	int text;
	int recty;

	start = 0;
	text = 0;
	recty = rect.y;
	if (game->orient[d] == BLUEDARK_PIXEL)
	{
		start = fmod(point.x[d], 100);
		text = 0;
	}
	else if (game->orient[d] == RED_PIXEL)
	{
		start = fmod(point.x[d], 100);
		text = 1;
	}
	else if (game->orient[d] == BLUE_PIXEL)
	{
		start = fmod(point.y[d], 100);
		text = 2;
	}
	else if (game->orient[d] == REDDARK_PIXEL)
	{
		start = fmod(point.y[d], 100);
		text = 3;
	}
	float scale_x = (float)game->texture[text].width / 100.0;
	float scale_y = (float)game->texture[text].height / (rect.height);
	if (rect.height > WINDOW_HEIGHT)
		rect.height = WINDOW_HEIGHT;
	if (rect.y < 0)
	{
		i = 0;
		recty = 0;
	}
	else
		i = rect.y;
	while (i < recty + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			int src_x = ((j - rect.x) * scale_x) + (start * scale_x);
			int src_y = ((i - rect.y) * scale_y);
			unsigned int pixel = get_pixel(game->texture[text].addr, src_x, src_y, game->texture[text].line_len, game->texture[text].bpp);
			img_pix_put(&game->img, j++, i, pixel);
		}
		++i;
	}
	return (0);
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
	int	i;
	double	angle;
	double len;
	double incrangle;
	t_point p;
	t_pointt point;

	incrangle = 90.0 / (double)WINDOW_WIDTH;
	i = WINDOW_WIDTH - 1;
	if (game->angle < 45)
		angle = 360.0 - (45.0 - game->angle);
	else
		angle = game->angle - 45.0;
	while (i >= 0)
	{
		p.x = game->posx;
		p.y = game->posy;
		while (!check_wall(p.x, p.y, game))
		{
			p = intersection(p.x, p.y, angle, game);
		}
		point.x[i] = p.x;
		point.y[i] = p.y;
		game->orient[i] = game->color;
		if (angle >= 359.955)
			angle = 0;
		else
			angle += incrangle;
		i--;
	}
	i = WINDOW_WIDTH - 1;
	while (i >= 0)
	{
		double d = distance(game->posx, game->posy, point.x[i], point.y[i]);
		len = 1;
		render_rect((t_rect){i, ((double)WINDOW_HEIGHT / 2.0) - ((((double)WINDOW_HEIGHT / d) * 100.0) / 2.0), len, ((double)WINDOW_HEIGHT / d) * 100.0, game->color}, game, point, i);
		i--;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.mlx_img, 0, 0);
	return (0);
}

/*int	render(t_data *game)
{	
	int	i;
	double	angle;
	double len;
	double incrangle;
	t_point p;
	t_pointt point;

	incrangle = 90.0 / (double)WINDOW_WIDTH;
	i = 0;
	if (game->angle < 45)
		angle = 360.0 - (45.0 - game->angle);
	else
		angle = game->angle - 45.0;
	while (i < WINDOW_WIDTH)
	{
		p.x = game->posx;
		p.y = game->posy;
		while (!check_wall(p.x, p.y, game))
		{
			p = intersection(p.x, p.y, angle, game);
		}
		point.x[i] = p.x;
		point.y[i] = p.y;
		game->orient[i] = game->color;
		if (angle >= 359.955)
			angle = 0;
		else
			angle += incrangle;
		i++;
	}
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		double d = distance(game->posx, game->posy, point.x[i], point.y[i]);
		len = 1;
		render_rect((t_rect){i, ((double)WINDOW_HEIGHT / 2.0) - ((((double)WINDOW_HEIGHT / d) * 100.0) / 2.0), len, ((double)WINDOW_HEIGHT / d) * 100.0, game->color}, game, point, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.mlx_img, 0, 0);
	return (0);
}*/

int	render_next_frame(t_data *game)
{
	render_background(&game->img, game);
	render(game);
	return (0);
}