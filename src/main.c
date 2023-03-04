#include "../includes/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
    pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

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

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

void	free_map(t_data *game)
{
	int	i;

	i = 0;
	while (game->map[i])
		free(game->map[i++]);
	free(game->map);
}

int	end(t_data *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	free_map(game);
	exit(0);
	return (0);
}

int	mykey_hook(int keycode, t_data *game)
{	
	if (keycode == XK_Escape)
		end(game);
	return (0);
}

int	render_next_frame(t_data *game)
{
	render_background(&game->img, BLACK_PIXEL);
	render_rect(&game->img, (t_rect){0 + (WINDOW_WIDTH / 90), 100, 10, 1000, WHITE_PIXEL});
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.mlx_img, 0, 0);
	return (0);
}

int	check_file(t_data *game)
{
	if (game->map == NULL)
	{
		ft_printf("Error\nMap file not found\n");
		return (1);
	}
	return (0);
}

void	parse_map(int fd, t_data *game)
{
	char	*str;

	str = get_next_line(fd);
	if (str == 0)
	{
		ft_printf("Empty file\nYour map must contain 1, C, P, 0 and E\n");
		exit(0);
	}
	game->map = ft_split(str, '\n');
	free(str);
}

int	set_map(char **str, t_data *game)
{
	int	fd;

	fd = 0;
	game->map = NULL;
	if (ft_strnstr(str[1], ".cub", 100) == 0)
	{
		ft_printf("Error\nNo correct format map finded (.cub)\n");
		return (1);
	}
	else
	{
		fd = open(str[1], O_RDONLY);
		if (fd > 0)
			parse_map(fd, game);
	}
	if (check_file(game))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	game;
	int		i;

	i = 0;
	if (argc != 2)
	{
		ft_printf("Error\nThis program needs one argument .cub\n");
		return (0);
	}
	if (set_map(argv, &game))
		return (0);
	else
	{
        game.win_width = 1000;
        game.win_height = 1000;
        while (game.map[i])
            printf("%s\n", game.map[i++]);
        game.mlx = mlx_init();
        game.mlx_win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
		game.img.mlx_img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		game.img.addr = mlx_get_data_addr(game.img.mlx_img, &game.img.bpp, &game.img.line_len, &game.img.endian);
        render_next_frame(&game);
		mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, mykey_hook, &game);
		mlx_hook(game.mlx_win, 17, 0, end, &game);
		mlx_loop(game.mlx);
	}
}