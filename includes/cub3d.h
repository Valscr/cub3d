/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 16:37:49 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 23:28:52 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include <X11/keysym.h> 
# include <X11/X.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define WINDOW_WIDTH 1300
# define WINDOW_HEIGHT 1000
# define GREEN_PIXEL 0x54FA3A
# define SPEED_ROTATE 4
# define SPEED_F_B 10
# define SPEED_L_R 8
# define NORTH 0
# define SOUTH 1
# define WEST 3
# define EAST 2

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bpp;
	int		width;
	int		height;
	int		line_len;
	int		endian;
}	t_texture;

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

typedef struct s_rect
{
	double	x;
	double	y;
	double	width;
	double	height;
	int		color;
}	t_rect;

typedef struct s_data
{	
	void		*mlx;
	void		*mlx_win;
	double		posx;
	double		posy;
	int			angle;
	int			nsew;
	int			color_floor;
	int			color_ceiling;
	int			forward;
	int			back;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
	float		scale_x;
	float		scale_y;
	int			orient[WINDOW_WIDTH];
	char		**map;
	char		**name_texture;
	t_img		img;
	t_texture	*texture;
}				t_data;

void			init(t_data *game);
char			*ft_strjoin1(char *s1, char *s2);
char			*ft_cut_dest(char *dest);
char			*new_save(char *dest);
char			*get_next(char *save, int fd);
char			*get_next_line(int fd);
double			distance(double x, double y, double x2, double y2);
char			**ft_split2(char const *s, char const *sep);
int				free_tab_str(char **str);
void			free_str(char *str);
void			free_map(t_data *game);
int				count_tab(char **str, int x, int y);
int				count_tab_full(char **str);
int				count_x(char *str, int x);
int				check_wall(double x, double y, t_data *game);
int				key_press(int keycode, t_data *game);
int				key_release(int keycode, t_data *game);
void			move_forward(t_data *game);
void			move_backward(t_data *game);
void			move_left(t_data *game);
void			move_right(t_data *game);
void			rotate(t_data *game);
void			set_pos_player(char c, int y, int x, t_data *game);
int				copy_map(char **str, t_data *game);
int				copy_map_bis(int j, int i, t_data *game, char **str);
int				find_one(char *str);
int				check_wall_first_last(char **str);
int				check_wall_map_bis(char **str, int i, int j);
int				check_wall_map(char **str);
int				ft_strlen_lesspace(char *str);
int				find_one(char *str);
int				parse_map_true(char **str, t_data *game);
int				parse_map(int fd, t_data *game);
int				set_map(char **str, t_data *game);
int				find_int(char *str);
int				convert_hex(char *str);
int				convert_hex_bis(char **string, int r, int g, int b);
char			*put_image_file(char *str);
int				parse_map_texture_color(char **str, t_data *game);
int				is_xpm_file(char *filename);
void			parse_xpm(t_data *game);
void			img_pix_put(t_img *img, int x, int y, int color);
unsigned int	get_pixel(t_data *game, int x, int y, int orient);
int				render_rect(t_rect rect, t_data *game, t_pointt point, int d);
int				render_rect_bis(t_rect rect, double start, t_data *game, int d);
int				loop_render_rect(int i, t_pointt point, t_data *game);
void			render_background(t_img *img, t_data *game);
int				render(t_data *game);
int				render_next_frame(t_data *game);
int				end(t_data *game);
t_point			intersection(double x, double y, double angle, t_data *game);
t_point			inter_0to90(double x, double y, double angle, t_data *game);
t_point			inter_90to180(double x, double y, double angle, t_data *game);
t_point			inter_180to270(double x, double y, double angle, t_data *game);
t_point			inter_270to360(double x, double y, double angle, t_data *game);
t_point			inter_0or180(double x, double y, double angle, t_data *game);
t_point			inter_90or270(double x, double y, double angle, t_data *game);
t_point			calculate_endpt(double x, double y, double angle, double len);
t_point			endpt_0to90(double x, double y, double angle, double len);
t_point			endpt_90to180(double x, double y, double angle, double len);
t_point			endpt_180to270(double x, double y, double angle, double len);
t_point			endpt_270to360(double x, double y, double angle, double len);
t_point			endpt_round(double x, double y, double angle, double len);
double			set_xlen(double x);
double			set_ylen(double y);
void			render_sight(t_img *img);

#endif