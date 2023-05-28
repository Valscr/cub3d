#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <X11/keysym.h> 
# include <X11/X.h>
# include <fcntl.h>
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
	int		bpp; /* bits per pixel */
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
	int		orient[WINDOW_WIDTH];
	char	**map;
	char	*name_texture[4];
    t_img	img;
	t_texture texture[4];
}				t_data;

char	*ft_strjoin1(char *s1, char *s2);
char	*ft_cut_dest(char *dest);
char	*new_save(char *dest);
char	*get_next(char *save, int fd);
char	*get_next_line(int fd);

#endif