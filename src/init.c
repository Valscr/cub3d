/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:52:33 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:49:20 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init(t_data *game)
{
	int	i;

	i = 0;
	game->posx = 0;
	game->posy = 0;
	game->angle = 0;
	game->nsew = 0;
	game->color_floor = 0;
	game->color_ceiling = 0;
	game->scale_x = 0.0;
	game->scale_y = 0.0;
	game->map = NULL;
	game->mlx = NULL;
	game->mlx_win = NULL;
	game->img.mlx_img = NULL;
	game->img.addr = NULL;
	game->name_texture = malloc(sizeof(char *) * 5);
	game->texture = malloc(sizeof(t_texture) * 5);
	while (i < 5)
	{
		game->name_texture[i] = NULL;
		game->texture[i].img = NULL;
		game->texture[i].addr = NULL;
		i++;
	}
}
