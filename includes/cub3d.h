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
#define GREEN_PIXEL 0xFF00
#define WHITE_PIXEL 0xFFFFFF
#define WHITE_PIXEL 0xFFFFFF
#define BLACK_PIXEL 0x000000
#define GREY_PIXEL 0x808080
#define BLUE_PIXEL 0x0000FF

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_rect
{
	int	x;
	int	y;
	int width;
	int height;
	int color;
}	t_rect;

typedef struct s_data
{	
	void	*mlx;
	void	*mlx_win;
	int		posx;
	int		posy;
	int		angle;
	char	**map;
    t_img	img;
	int		win_width;
	int		win_height;
}				t_data;

char	*ft_strjoin1(char *s1, char *s2);
char	*ft_cut_dest(char *dest);
char	*new_save(char *dest);
char	*get_next(char *save, int fd);
char	*get_next_line(int fd);

#endif