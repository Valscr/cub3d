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

void	render_mini_map(t_img *img, t_data *game)
{
	int		i;
	int		j;
	t_rect	rec;

	i = 0;
	rec.width = WINDOW_WIDTH / 5 / find_max_width(game);
	rec.height = WINDOW_HEIGHT / 5 / count_tab_full(game->map);
	while (i < count_tab_full(game->map))
	{
		j = 0;
		while (j < ft_strlen(game->map[i]))
		{
			rec.x = j * rec.width;
			rec.y = i * rec.height;
			if (game->map[i][j++] == '1')
				rec.color = 0x000000;
			else
				rec.color = 0xFFFFFF;
			fill_rect(img, rec);
		}
		i++;
	}
	fill_rect(img, (t_rect){(game->posx - 50) / 100 * rec.width + rec.width / 2
		- rec.width / 20, (game->posy - 50) / 100 * rec.height + rec.height / 2
		- rec.height / 20, rec.width / 9, rec.height / 9, 0x0000FF});
}
