#include "../includes/cub3d.h"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

double distance(int x, int y, int x2, int y2)
{
    double dx = x2 - x;
    double dy = y2 - y;
    return sqrt(dx*dx + dy*dy);
}

t_point intersection(double x, double y, int angle, t_data *game)
{
	t_point	p;
	float	tanValue = tan(angle * M_PI / 180);

	p.x = 0;
	p.y = 0;
	double xlen = 0;
	double ylen = 0;
	double size = 100;
	if (angle == 0)
	{
		p.x = x;
		p.y = y + (size - fmod(y, size));
		game->color = RED_PIXEL;
	}
	else if (angle == 180)
	{
		if (fmod(y, size) != 0)
			ylen = fmod(y, size);
		else if (y == 0)
			ylen = 0;
		else
			ylen = size;
		p.x = x;
		p.y = y - (ylen);
		game->color = BLUEDARK_PIXEL;
	}
	else if (angle == 90)
	{
		p.x = x + (size - fmod(x, size));
		p.y = y;
		game->color = REDDARK_PIXEL;
	}
	else if (angle == 270)
	{
		if (fmod(x, size) != 0)
			xlen = fmod(x, size);
		else if (x == 0)
			xlen = 0;
		else
			xlen = size;
		p.x = x - (xlen);
		p.y = y;
		game->color = BLUE_PIXEL;
	}
	else if (angle > 0 && angle < 90)
	{
		xlen = size - fmod(x, size);
		ylen = size - fmod(y, size);
		if (tanValue * ylen < (xlen))
		{
			p.x = x + tanValue * ylen;
			p.y = y + ylen;
			game->color = RED_PIXEL;
		}
		else
		{
			p.x = x + xlen;
			tanValue = tan((45 - (angle - 45)) * M_PI / 180);
			p.y = y + tanValue * xlen;
			game->color = REDDARK_PIXEL;
		}
	}
	else if (angle > 90 && angle < 180)
	{
		xlen = size - fmod(x, size);
		if (fmod(y, size) != 0)
			ylen = fmod(y, size);
		else if (y == 0)
			ylen = 0;
		else
			ylen = size;
		tanValue = tan((angle - 90) * M_PI / 180);
		if (tanValue * xlen < (ylen))
		{
			p.x = x + xlen;
			p.y = y - tanValue * xlen;
			game->color = REDDARK_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 135)) * M_PI / 180);
			p.x = x + tanValue * ylen;
			p.y = y - ylen;
			game->color = BLUEDARK_PIXEL;
		}
	}
	else if (angle > 180 && angle < 270)
	{
		if (fmod(x, size) != 0)
			xlen = fmod(x, size);
		else if (x == 0)
			xlen = 0;
		else
			xlen = size;
		if (fmod(y, size) != 0)
			ylen = fmod(y, size);
		else if (y == 0)
			ylen = 0;
		else
			ylen = size;
		tanValue = tan((angle - 180) * M_PI / 180);
		if (tanValue * ylen < xlen)
		{
			p.x = x - tanValue * ylen;
			p.y = y - ylen;
			game->color = BLUEDARK_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 225)) * M_PI / 180);
			p.x = x - xlen;
			p.y = y - tanValue * xlen;
			game->color = BLUE_PIXEL;
		}
	}
	else if (angle > 270 && angle < 360)
	{
		ylen = size - fmod(y, size);
		if (fmod(x, size) != 0)
			xlen = fmod(x, size);
		else if (x == 0)
			xlen = 0;
		else
			xlen = size;
		tanValue = tan((angle - 270) * M_PI / 180);
		if (tanValue * xlen < ylen)
		{
			p.x = x - xlen;
			p.y = y + tanValue * xlen;
			game->color = BLUE_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 315)) * M_PI / 180);
			p.x = x - tanValue * ylen;
			p.y = y + ylen;
			game->color = RED_PIXEL;
		}
	}
	return (p);
}

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
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, GREY_PIXEL);
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

int	count_tab(char **str, int x, int y)
{
	int	i;

	i = y / 100;
	if (str[0] == 0)
		return (i);
	while (str[i])
	{
		if (str[i][x / 100] == '0')
		{
			while (str[i][x / 100])
			{
				if (str[i][x / 100] == '1')
					return (i);
				i++;
			}
		}
		i++;
	}
	return (i);
}

int	count_x(char *str, int x)
{
	int	i;

	i = x / 100;
	while (str[i])
	{
		if (str[i] == '0')
		{
			while (str[i])
			{
				if (str[i] == '1')
					return (i);
				i++;
			}
			return (i);
		}
		i++;
	}
	return (i);
}

int	check_wall(double x, double y, t_data *game)
{
	int xIndex, yIndex;

	if (x < ((count_x(game->map[(int)roundf(y) / 100], (int)roundf(x)) - 1) * 100))
		xIndex = (int)ceil((double)x / 100);
	else
		xIndex = roundf(x) / 100;

	if (y < (count_tab(game->map, (int)roundf(x), (int)roundf(y)) - 1) * 100)
		yIndex = (int)ceil((double)y / 100);
	else
		yIndex = roundf(y) / 100;
	
	if (game->map[yIndex][xIndex] == '1')
		return (1);
	return (0);
}

int	render(t_data *game)
{	
	int	i;
	int	angle;
	int len;
	t_point p;

	i = -1;
	if (game->angle < 45)
		angle = 360 - (45 - game->angle);
	else
		angle = game->angle - 45;
	while (i < 90)
	{
		p.x = game->posx;
		p.y = game->posy;
		while (!check_wall(p.x, p.y, game))
		{
			p = intersection(p.x, p.y, angle, game);
		}
		double d = distance(game->posx, game->posy, p.x, p.y);
		if (d < 100)
			d = 100;
		if (i == 89)
			len = WINDOW_WIDTH / 90 - 2;
		else
			len = WINDOW_WIDTH / 90;
		render_rect(&game->img, (t_rect){(WINDOW_WIDTH / 90) * (i + 1), (WINDOW_HEIGHT / 2) - (((WINDOW_HEIGHT / d) * 100) / 2), len, (WINDOW_HEIGHT / d) * 100, game->color});
		mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.mlx_img, 0, 0);
		if (angle == 359)
			angle = 0;
		else
			angle++;
		i++;
	}
	return (0);
}

int	render_next_frame(t_data *game)
{
	render_background(&game->img, BLACK_PIXEL);
	render(game);
	return (0);
}

t_point calculate_endpoint(double x, double y, int angle, double len)
{
    t_point point;

    double angle_rad =  tan(angle * M_PI / 180);
	point.x = x;
	point.y = y;
	if (angle == 270)
	{
		point.x = x - len;
		point.y = y;
	}
	if (angle == 180)
	{
		point.x = x;
		point.y = y - len;
	}
	if (angle == 90)
	{
		point.x = x + len;
		point.y = y;
	}
	if (angle == 0)
	{
		point.x = x;
		point.y = y + len;
	}
	if (angle > 0 && angle < 90)
	{
		if (angle <= 45)
		{
			point.x = x + len * sin(angle_rad);
    		point.y = y + len * cos(angle_rad);
		}
		else
		{
			angle_rad = tan((45 - (angle - 45)) * M_PI / 180);
			point.x = x + len * sin(angle_rad);
    		point.y = y + len * cos(angle_rad);
		}
	}
	if (angle > 90 && angle < 180)
	{
		angle_rad = tan((angle - 90) * M_PI / 180);
		if (angle <= 135)
		{
			point.x = x + len * cos(angle_rad);
    		point.y = y - len * sin(angle_rad);
		}
		else
		{
			angle_rad = tan((45 - (angle - 135)) * M_PI / 180);
			point.x = x + len * cos(angle_rad);
    		point.y = y - len * sin(angle_rad);
		}
	}
	if (angle > 180 && angle < 270)
	{
		angle_rad = tan((angle - 180) * M_PI / 180);
		if (angle <= 225)
		{
			point.x = x - len * sin(angle_rad);
    		point.y = y - len * cos(angle_rad);
		}
		else
		{
			angle_rad = tan((45 - (angle - 225)) * M_PI / 180);
			point.x = x - len * sin(angle_rad);
    		point.y = y - len * cos(angle_rad);
		}
	}
	if (angle > 270 && angle < 360)
	{
		angle_rad = tan((angle - 270) * M_PI / 180);
		if (angle <= 315)
		{
			point.x = x - len * cos(angle_rad);
    		point.y = y + len * sin(angle_rad);
		}
		else
		{
			angle_rad = tan((45 - (angle - 315)) * M_PI / 180);
			point.x = x - len * cos(angle_rad);
    		point.y = y + len * sin(angle_rad);
		}
	}
    return point;
}

int	mykey_hook(int keycode, t_data *game)
{	
	t_point point;
	int angle;

	if (keycode == XK_Escape)
		end(game);
	else if (keycode == XK_Up)
	{
		angle = game->angle;
		point = calculate_endpoint(game->posx, game->posy, angle, 50);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
			render_next_frame(game);
		}
	}
	else if (keycode == XK_Right)
	{
		if (game->angle >= 270)
			angle = game->angle + 90 - 360;
		else
			angle = game->angle + 90;
		point = calculate_endpoint(game->posx, game->posy, angle, 50);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
			render_next_frame(game);
		}
	}
	else if (keycode == XK_Left)
	{
		if (game->angle < 90)
			angle = game->angle - 90 + 360;
		else
			angle = game->angle - 90;
		point = calculate_endpoint(game->posx, game->posy, angle, 50);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
			render_next_frame(game);
		}
	}
	else if (keycode == XK_Down)
	{
		if (game->angle < 180)
			angle = game->angle - 180 + 360;
		else
			angle = game->angle - 180;
		point = calculate_endpoint(game->posx, game->posy, angle, 50);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
			render_next_frame(game);
		}
	}
	else if (keycode == XK_r)
	{
		if (game->angle >= 340)
			game->angle += 20 - 360;
		else
			game->angle += 20;
		render_next_frame(game);
	}
	else if (keycode == XK_t)
	{
		if (game->angle < 20)
			game->angle += -20 + 360;
		else
			game->angle -= 20;
		render_next_frame(game);
	}
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
		game.posx = 2000;
		game.posy = 400;
		game.angle = 270;
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