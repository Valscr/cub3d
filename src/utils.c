/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:09:37 by valentin          #+#    #+#             */
/*   Updated: 2023/05/31 22:41:59 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double distance(double x, double y, double x2, double y2)
{
    double dx = x2 - x;
    double dy = y2 - y;
    return sqrt(dx*dx + dy*dy);
}

int	end(t_data *game)
{
	if (game->texture[0].img)
		mlx_destroy_image(game->mlx, game->texture[0].img);
	if (game->texture[1].img)
		mlx_destroy_image(game->mlx, game->texture[1].img);
	if (game->texture[2].img)
		mlx_destroy_image(game->mlx, game->texture[2].img);
	if (game->texture[3].img)
		mlx_destroy_image(game->mlx, game->texture[3].img);
	if (game->img.mlx_img)
		mlx_destroy_image(game->mlx, game->img.mlx_img);
	if (game->mlx_win)
		mlx_destroy_window(game->mlx, game->mlx_win);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	if (game->mlx)
		free(game->mlx);
	if (game->texture)
		free(game->texture);
	if (game->name_texture)
		free_tab_str(game->name_texture);
	if (game->map != NULL)
		free_tab_str(game->map);
	exit(0);
	return (0);
}