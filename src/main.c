/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:09:54 by valentin          #+#    #+#             */
/*   Updated: 2023/05/31 22:57:25 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int myFunction(void *game)
{
	t_data *data = (t_data*)game;
	render_next_frame(data);
    return 0;
}

int	main(int argc, char **argv)
{
	t_data	game;

	if (argc != 2)
	{
		ft_printf("Error\nThis program needs one argument .cub\n");
		return (0);
	}
	init(&game);
	if (set_map(argv, &game))
		return (end(&game), 0);
	else
	{
        game.mlx = mlx_init();
        game.mlx_win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
		game.img.mlx_img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		game.img.addr = mlx_get_data_addr(game.img.mlx_img, &game.img.bpp, &game.img.line_len, &game.img.endian);
       	parse_xpm(&game);
	  	render_next_frame(&game);
		mlx_hook(game.mlx_win, 17, 0, end, &game);
		mlx_hook(game.mlx_win, KeyPress, KeyPressMask, mykey_hook, &game);
		mlx_loop_hook(game.mlx, myFunction, (void*)&game);
		mlx_loop(game.mlx);
	}
	return (0);
}