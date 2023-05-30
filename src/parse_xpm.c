/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:18:27 by valentin          #+#    #+#             */
/*   Updated: 2023/05/30 13:21:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int is_xpm_file(char* filename)
{
    int fd;

	if (ft_strnstr(filename, ".xpm", 100) == NULL)
		return (write(2, "Error : No correct format image finded (.xpm)\n", 46), 0);
	fd = open(filename, O_RDONLY);
    if (fd < 1)
        return (write(2, "Error : missing image(s) in xpm format\n", 39), 0);
	else
		close(fd);
	return (1);
}

int	parse_xpm(t_data *game)
{
	int i;

	i = 0;
	while (i < 4)
	{
		if (is_xpm_file(game->name_texture[i]))
		{
			game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
					game->name_texture[i], &game->texture[i].width,
					&game->texture[i].height);
			game->texture[i].addr = mlx_get_data_addr(game->texture[i].img, &game->texture[i].bpp, &game->texture[i].line_len, &game->texture[i].endian);
		}
		else
			return (1);
		i++;
		
	}
	return (0);
}