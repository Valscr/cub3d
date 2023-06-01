/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:23:35 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:41:31 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_hook(int keycode, t_data *game)
{	
	if (keycode == XK_Escape)
		end(game);
	else if (keycode == XK_Up)
		move_forward(game);
	else if (keycode == XK_Left)
		move_left(game);
	else if (keycode == XK_Right)
		move_right(game);
	else if (keycode == XK_Down)
		move_backward(game);
	else if (keycode == XK_r || keycode == XK_t)
		rotate(game, keycode);
	return (0);
}
