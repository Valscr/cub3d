/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 00:20:55 by marvin            #+#    #+#             */
/*   Updated: 2023/06/03 00:20:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	fill_rect(t_img *img, t_rect rect)
{
	int		i;
	int		j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	fill_circle(t_img *img, t_rect rect)
{
	int	center_x;
	int	center_y;
	int	radius;
	int	x;
	int	y;

	center_x = rect.x + rect.width / 2;
	center_y = rect.y + rect.height / 2;
	radius = rect.width / 2;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			if (pow(x - center_x, 2) + pow(y - center_y, 2) <= pow(radius, 2))
				img_pix_put(img, x, y, rect.color);
			x++;
		}
		y++;
	}
	return (0);
}

int	find_max_width(t_data *game)
{
	int	wdh;
	int	hgt;
	int	i;
	int	len;

	hgt = count_tab_full(game->map);
	i = 0;
	wdh = 0;
	while (i < hgt)
	{
		len = ft_strlen(game->map[i]);
		if (wdh < len)
			wdh = len;
		i++;
	}
	return (wdh);
}

void	draw_minimap(t_data *game, int i, t_rect rec, t_img *img)
{
	int	j;

	j = 0;
	while (j <= ft_strlen_lesspace(game->map[i]))
	{
		rec.x = j * rec.width + 5.0;
		rec.y = i * rec.height + 5.0;
		if (game->map[i][j] == '1')
		{
			rec.color = 0x000000;
			fill_rect(img, rec);
		}
		else if ((check_close_all(game->map, j, i) && game->map[i][j] == ' ')
			|| game->map[i][j] == '0' || game->map[i][j] == 'N'
			|| game->map[i][j] == 'S' || game->map[i][j] == 'E'
			|| game->map[i][j] == 'W')
		{
			rec.color = 0xFFFFFF;
			fill_rect(img, rec);
		}
		j++;
	}
	return ;
}

void	render_mini_map(t_img *img, t_data *game)
{
	int		i;
	t_rect	rec;
	double	size_player;

	i = 0;
	if (find_max_width(game) < count_tab_full(game->map))
		rec.width = WINDOW_HEIGHT / 4.0 / count_tab_full(game->map);
	else
		rec.width = WINDOW_WIDTH / 4.0 / find_max_width(game);
	rec.height = rec.width;
	while (i < count_tab_full(game->map))
		draw_minimap(game, i++, rec, img);
	if (rec.width / 3.0 > 12.0)
		size_player = 12.0;
	else if (rec.width / 3.0 < 6.0)
		size_player = 6.0;
	else
		size_player = rec.width / 3.0;
	fill_circle(img, (t_rect){(game->posx) / 100.0 * rec.width - size_player
		/ 2.0 + 5.0, (game->posy) / 100.0 * rec.height - size_player
		/ 2.0 + 5.0, size_player, size_player, 0xFF0000});
}
