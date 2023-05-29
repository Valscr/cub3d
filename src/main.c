#include "../includes/cub3d.h"

typedef struct s_point
{
	double	x;
	double	y;
}	t_point;

typedef struct s_pointt
{
	double	x[WINDOW_WIDTH];
	double	y[WINDOW_WIDTH];
}	t_pointt;

double distance(double x, double y, double x2, double y2)
{
    double dx = x2 - x;
    double dy = y2 - y;
    return sqrt(dx*dx + dy*dy);
}

t_point intersection(double x, double y, double angle, t_data *game)
{
	t_point	p;
	float	tanValue = tan(angle * (M_PI / 180));

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
			tanValue = tan((45 - (angle - 45)) * (M_PI / 180));
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
		tanValue = tan((angle - 90) * (M_PI / 180));
		if (tanValue * xlen < (ylen))
		{
			p.x = x + xlen;
			p.y = y - tanValue * xlen;
			game->color = REDDARK_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 135)) * (M_PI / 180));
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
		tanValue = tan((angle - 180) * (M_PI / 180));
		if (tanValue * ylen < xlen)
		{
			p.x = x - tanValue * ylen;
			p.y = y - ylen;
			game->color = BLUEDARK_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 225)) * (M_PI / 180));
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
		tanValue = tan((angle - 270) * (M_PI / 180));
		if (tanValue * xlen < ylen)
		{
			p.x = x - xlen;
			p.y = y + tanValue * xlen;
			game->color = BLUE_PIXEL;
		}
		else
		{
			tanValue = tan((45 - (angle - 315)) * (M_PI / 180));
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

unsigned int get_pixel(char *addr, int x, int y, int line_len, int bpp)
{
	unsigned int *pixel_ptr = (unsigned int *)(addr + (y * line_len) + (x * (bpp / 8)));
	return *pixel_ptr;
}


int render_rect(t_rect rect, t_data *game, t_pointt point, int d)
{
	double	i;
	double j;
	double start;
	int text;
	int recty;

	start = 0;
	text = 0;
	recty = rect.y;
	if (game->orient[d] == BLUEDARK_PIXEL)
	{
		start = fmod(point.x[d], 100);
		text = 0;
	}
	else if (game->orient[d] == RED_PIXEL)
	{
		start = fmod(point.x[d], 100);
		text = 1;
	}
	else if (game->orient[d] == BLUE_PIXEL)
	{
		start = fmod(point.y[d], 100);
		text = 2;
	}
	else if (game->orient[d] == REDDARK_PIXEL)
	{
		start = fmod(point.y[d], 100);
		text = 3;
	}
	float scale_x = (float)game->texture[text].width / 100.0;
	float scale_y = (float)game->texture[text].height / (rect.height);
	if (rect.height > WINDOW_HEIGHT)
		rect.height = WINDOW_HEIGHT;
	if (rect.y < 0)
	{
		i = 0;
		recty = 0;
	}
	else
		i = rect.y;
	while (i < recty + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			int src_x = ((j - rect.x) * scale_x) + (start * scale_x);
			int src_y = ((i - rect.y) * scale_y);
			unsigned int pixel = get_pixel(game->texture[text].addr, src_x, src_y, game->texture[text].line_len, game->texture[text].bpp);
			img_pix_put(&game->img, j++, i, pixel);
		}
		++i;
	}
	return (0);
}

void	render_background(t_img *img, t_data *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT / 2)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, game->color_ceiling);
		}
		++i;
	}
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
		{
			img_pix_put(img, j++, i, game->color_floor);
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

	if (x < ((count_x(game->map[(int)y / 100], (int)x) - 1) * 100))
		xIndex = (int)ceil((double)x / 100.0);
	else
		xIndex = x / 100.0;

	if (y < (count_tab(game->map, (int)x, (int)y) - 1) * 100)
		yIndex = (int)ceil((double)y / 100.0);
	else
		yIndex = y / 100.0;
	
	if (game->map[yIndex][xIndex] == '1')
	{
		if (fmod(x, 100.0) != 0 && fmod(y, 10.00) != 0)
			return (0);
		else
			return (1);
	}
	return (0);
}

int	render(t_data *game)
{	
	int	i;
	double	angle;
	double len;
	double incrangle;
	t_point p;
	t_pointt point;

	incrangle = 90.0 / (double)WINDOW_WIDTH;
	i = 0;
	if (game->angle < 45)
		angle = 360.0 - (45.0 - game->angle);
	else
		angle = game->angle - 45.0;
	while (i < WINDOW_WIDTH)
	{
		p.x = game->posx;
		p.y = game->posy;
		while (!check_wall(p.x, p.y, game))
		{
			p = intersection(p.x, p.y, angle, game);
		}
		point.x[i] = p.x;
		point.y[i] = p.y;
		game->orient[i] = game->color;
		if (angle >= 359.955)
			angle = 0;
		else
			angle += incrangle;
		i++;
	}
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		double d = distance(game->posx, game->posy, point.x[i], point.y[i]);
		len = 1;
		render_rect((t_rect){i, ((double)WINDOW_HEIGHT / 2.0) - ((((double)WINDOW_HEIGHT / d) * 100.0) / 2.0), len, ((double)WINDOW_HEIGHT / d) * 100.0, game->color}, game, point, i);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.mlx_img, 0, 0);
	return (0);
}

int	render_next_frame(t_data *game)
{
	render_background(&game->img, game);
	render(game);
	return (0);
}

t_point calculate_endpoint(double x, double y, double angle, double len)
{
    t_point point;

    double angle_rad =  tan(angle * (M_PI / 180.0));
	point.x = x;
	point.y = y;
	if (angle == 270.0)
	{
		point.x = x - len;
		point.y = y;
	}
	else if (angle == 180.0)
	{
		point.x = x;
		point.y = y - len;
	}
	else if (angle == 90.0)
	{
		point.x = x + len;
		point.y = y;
	}
	else if (angle == 0.0)
	{
		point.x = x;
		point.y = y + len;
	}
	else if (angle > 0.0 && angle < 90.0)
	{
		if (angle <= 45.0)
		{
			point.x = x + len * sin(angle_rad);
    		point.y = y + len * cos(angle_rad);
		}
		else
		{
			angle_rad = tan(((90.0 - angle)) * (M_PI / 180.0));
			point.x = x + len * cos(angle_rad);
    		point.y = y + len * sin(angle_rad);
		}
	}
	else if (angle > 90.0 && angle < 180.0)
	{
		angle_rad = tan((angle - 90.0) * (M_PI / 180.0));
		if (angle <= 135.0)
		{
			point.x = x + len * cos(angle_rad);
    		point.y = y - len * sin(angle_rad);
		}
		else
		{
			angle_rad = tan((90.0 - (angle - 90.0)) * (M_PI / 180.0));
			point.x = x + len * sin(angle_rad);
    		point.y = y - len * cos(angle_rad);
		}
	}
	else if (angle > 180.0 && angle < 270.0)
	{
		angle_rad = tan((angle - 180.0) * (M_PI / 180.0));
		if (angle <= 225.0)
		{
			point.x = x - len * sin(angle_rad);
    		point.y = y - len * cos(angle_rad);
		}
		else
		{
			angle_rad = tan((90.0 - (angle - 180.0)) * (M_PI / 180.0));
			point.x = x - len * cos(angle_rad);
    		point.y = y - len * sin(angle_rad);
		}
	}
	else if (angle > 270.0 && angle < 360.0)
	{
		angle_rad = tan((angle - 270.0) * (M_PI / 180.0));
		if (angle <= 315.0)
		{
			point.x = x - len * cos(angle_rad);
    		point.y = y + len * sin(angle_rad);
		}
		else
		{
			angle_rad = tan((90.0 - (angle - 270.0)) * (M_PI / 180.0));
			point.x = x - len * sin(angle_rad);
    		point.y = y + len * cos(angle_rad);
		}
	}
    return point;
}

int	mykey_hook(int keycode, t_data *game)
{	
	t_point point;
	double angle;

	angle = game->angle;
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
		if (game->angle >= 270.0)
			angle = game->angle - 270.0;
		else
			angle = game->angle + 90.0;
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
		if (game->angle < 90.0)
			angle = game->angle + 270.0;
		else
			angle = game->angle - 90.0;
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
		if (game->angle < 180.0)
			angle = game->angle + 180.0;
		else
			angle = game->angle - 180.0;
		point = calculate_endpoint(game->posx, game->posy, angle, 50);
		if (!check_wall(point.x, point.y, game))
		{
			game->posy = point.y;
			game->posx = point.x;
			render_next_frame(game);
		}
	}
	else if (keycode == XK_t)
	{
		if (game->angle >= 340.0)
			game->angle -= 340.0;
		else
			game->angle += 20.0;
		render_next_frame(game);
	}
	else if (keycode == XK_r)
	{
		if (game->angle < 20.0)
			game->angle += 340;
		else
			game->angle -= 20.0;
		render_next_frame(game);
	}
	return (0);
}
int convertToHex(char *str)
{
    char *hexDigits;
 	unsigned int color;
    char* hexColor;
	char **string;
	int i;
	int r;
	int g;
	int b;

	string = ft_split(str, ',');
	r = ft_atoi(string[0]);
	g = ft_atoi(string[1]);
	b = ft_atoi(string[2]);
	hexDigits = ft_strdup("0123456789ABCDEF");
	color = (r << 16) | (g << 8) | b;
	hexColor = (char*)malloc(6 * sizeof(char));
    if (r < 0) r = 0;
    if (r > 255) r = 255;
    if (g < 0) g = 0;
    if (g > 255) g = 255;
    if (b < 0) b = 0;
    if (b > 255) b = 255;
    hexColor[6] = '\0';

	i = 5;
	while (i >= 0) 
	{
        hexColor[i--] = hexDigits[color & 0xF];
        color >>= 4;
    }
	free(hexDigits);
	return (ft_atoi_base(hexColor, "0123456789ABCDEF"));
}

int	parse_map_texture_color(char **str, t_data *game)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == 'N' && str[i][1] == 'O' && str[i][2] == ' ')
			game->name_texture[0] = ft_strdup(&str[i][3]);
		else if (str[i][0] == 'S' && str[i][1] == 'O' && str[i][2] == ' ')
			game->name_texture[1] = ft_strdup(&str[i][3]);
		else if (str[i][0] == 'W' && str[i][1] == 'E' && str[i][2] == ' ')
			game->name_texture[2] = ft_strdup(&str[i][3]);
		else if (str[i][0] == 'E' && str[i][1] == 'A' && str[i][2] == ' ')
			game->name_texture[3] = ft_strdup(&str[i][3]);
		else if (str[i][0] == 'F' && str[i][1] == ' ')
			game->color_floor = convertToHex(&str[i][2]);
		else if (str[i][0] == 'C' && str[i][1] == ' ')
			game->color_ceiling = convertToHex(&str[i][2]);
		i++;
	}
	return (0);
}

int	find_one(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
			return (1);
		i++;
	}
	return (0);
}

int	copy_map(char **str, t_data *game)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	game->map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		game->map[i] = ft_strdup(str[i]);
		i++;
	}
	return (0);
}

int	parse_map_true(char **str, t_data *game)
{
	int i;

	i = 6;
	while (str[i])
	{
		if (str[i][0] != 'N' && str[i][0] != 'S' && str[i][0] != 'E' && str[i][0] != 'W'
			&& str[i][0] != 'F' && str[i][0] != 'C' && find_one(str[i]))
		{
			copy_map(&str[i], game);
			return (1);
		}
		i++;
	}
	return (0);
}

void	parse_map(int fd, t_data *game)
{
	char	*str;
	char	**full;

	str = get_next_line(fd);
	if (str == 0)
	{
		write(2, "Empty file\n", 12);
		exit(0);
	}
	full = ft_split(str, '\n');
	free(str);
	parse_map_texture_color(full, game);
	parse_map_true(full, game);
}

int	set_map(char **str, t_data *game)
{
	int	fd;

	fd = 0;
	game->map = NULL;
	if (ft_strnstr(str[1], ".cub", 100) == 0)
	{
		write(2, "Error\nNo correct format map finded (.cub)\n", 41);
		return (1);
	}
	else
	{
		fd = open(str[1], O_RDONLY);
		if (fd > 0)
			parse_map(fd, game);
	}
	return (0);
}

int myFunction(void *game)
{
	t_data *data = (t_data*)game;
	(void)data;
    return 0;
}

int	parse_xpm(t_data *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
					game->name_texture[i], &game->texture[i].width,
					&game->texture[i].height);
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, &game->texture[i].bpp, &game->texture[i].line_len, &game->texture[i].endian);
		i++;
	}
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
		game.posx = 2000;
		game.posy = 400;
		game.angle = 30;
        while (game.map[i])
            printf("%s\n", game.map[i++]);
        game.mlx = mlx_init();
        game.mlx_win = mlx_new_window(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "CUB3D");
		game.img.mlx_img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
		game.img.addr = mlx_get_data_addr(game.img.mlx_img, &game.img.bpp, &game.img.line_len, &game.img.endian);
       	parse_xpm(&game);
	  	render_next_frame(&game);
		mlx_hook(game.mlx_win, KeyRelease, KeyReleaseMask, mykey_hook, &game);
		mlx_hook(game.mlx_win, 17, 0, end, &game);
		/*mlx_loop_hook(game.mlx, myFunction, (void*)&game);*/
		mlx_loop(game.mlx);
	}
}