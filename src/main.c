/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:09:54 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 23:27:11 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	hook_function(void *game)
{
	render_next_frame((t_data *)game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
		return (write(2, "Error\nThis program needs one argument .cub\n", 44), 0);
	init(&game);
	if (set_map(argv, &game))
		return (end(&game), 0);
	else
	{
		game.mlx = mlx_init();
		game.mlx_win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
				"CUB3D");
		game.img.mlx_img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		game.img.addr = mlx_get_data_addr(game.img.mlx_img, &game.img.bpp,
				&game.img.line_len, &game.img.endian);
		parse_xpm(&game);
		render_next_frame(&game);
		mlx_hook(game.mlx_win, 17, 0, end, &game);
		mlx_hook(game.mlx_win, 2, 1L << 0, key_press, &game);
		mlx_hook(game.mlx_win, 3, 1L << 1, key_release, &game);
		mlx_loop_hook(game.mlx, hook_function, (void *)&game);
		mlx_loop(game.mlx);
	}
	return (0);
}
