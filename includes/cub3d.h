#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <X11/keysym.h> 
# include <X11/X.h>
# include <fcntl.h>
#include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

#define WINDOW_WIDTH 2000
#define WINDOW_HEIGHT 1500
#define RED_PIXEL 0xFF0000
#define REDDARK_PIXEL 0xCC0000
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x000000
#define GREY_PIXEL 0x808080
#define BLUE_PIXEL 0x0000FF
#define BLUEDARK_PIXEL 0x0000B3
#define YELLOW_PIXEL 0xFFFF00

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
	double width;
	double height;
	int color;
}	t_rect;

typedef struct s_data
{	
	void	*mlx;
	void	*mlx_win;
	double		posx;
	double		posy;
	int		angle;
	int		color;
	int		color_floor;
	int		color_ceiling;
	int		orient[WINDOW_WIDTH];
	char	**map;
	char	**name_texture;
    t_img	img;
	t_texture *texture;
}				t_data;

void init(t_data *game);
char	*ft_strjoin1(char *s1, char *s2);
char	*ft_cut_dest(char *dest);
char	*new_save(char *dest);
char	*get_next(char *save, int fd);
char	*get_next_line(int fd);
double distance(double x, double y, double x2, double y2);
char	**ft_split2(char const *s, char const *sep);
int		free_tab_str(char **str);
void	free_str(char *str);
void	free_map(t_data *game);
int	count_tab(char **str, int x, int y);
int	count_tab_full(char **str);
int	count_x(char *str, int x);
int	check_wall(double x, double y, t_data *game);
t_point intersection(double x, double y, double angle, t_data *game);
t_point calculate_endpoint(double x, double y, double angle, double len);
int	mykey_hook(int keycode, t_data *game);
void	set_pos_player(char c, int y, int x, t_data *game);
int	copy_map(char **str, t_data *game);
int	find_one(char *str);
int	parse_map_true(char **str, t_data *game);
int	parse_map(int fd, t_data *game);
int	set_map(char **str, t_data *game);
int find_int(char *str);
int convertToHex(char *str);
char	*put_image_file(char *str);
int	parse_map_texture_color(char **str, t_data *game);
int is_xpm_file(char* filename);
void	parse_xpm(t_data *game);
void	img_pix_put(t_img *img, int x, int y, int color);
unsigned int get_pixel(char *addr, int x, int y, int line_len, int bpp);
int render_rect(t_rect rect, t_data *game, t_pointt point, int d);
void	render_background(t_img *img, t_data *game);
int	render(t_data *game);
int	render_next_frame(t_data *game);
int	end(t_data *game);
void	create_tab_int(char **str, t_data *game);
void free_all(t_data *game);

#endif