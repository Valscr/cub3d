/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:35 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 19:31:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(int keycode, t_data *game)
{	
	if (keycode == XK_Escape)
		end(game);
	else if (keycode == XK_Up)
		game->forward = 1;
	else if (keycode == XK_Left)
		game->left = 1;
	else if (keycode == XK_Right)
		game->right = 1;
	else if (keycode == XK_Down)
		game->back = 1;
	else if (keycode == XK_r)
		game->rotate_left = 1;
	else if (keycode == XK_t)
		game->rotate_right = 1;
	return (0);
}

int	key_release(int keycode, t_data *game)
{	
	if (keycode == XK_Escape)
		end(game);
	else if (keycode == XK_Up)
		game->forward = 0;
	else if (keycode == XK_Left)
		game->left = 0;
	else if (keycode == XK_Right)
		game->right = 0;
	else if (keycode == XK_Down)
		game->back = 0;
	else if (keycode == XK_r)
		game->rotate_left = 0;
	else if (keycode == XK_t)
		game->rotate_right = 0;
	return (0);
}
