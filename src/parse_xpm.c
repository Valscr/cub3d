/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:18:27 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:17:37 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*put_image_file(char *str)
{
	int		i;
	char	*string;

	i = 0;
	string = NULL;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (NULL);
	string = ft_strdup(&str[i]);
	return (string);
}

int	is_xpm_file(char *filename)
{
	int	fd;

	if (ft_strnstr(filename, ".xpm", 100) == NULL)
		return (write(2, "Error : No correct format image finded (.xpm)\n",
				46), 0);
	fd = open(filename, O_RDONLY);
	if (fd < 1)
		return (write(2, "Error : missing image(s) in xpm format\n", 39), 0);
	else
		close(fd);
	return (1);
}

void	parse_xpm(t_data *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->texture[i].img = mlx_xpm_file_to_image(game->mlx,
				game->name_texture[i], &game->texture[i].width,
				&game->texture[i].height);
		game->texture[i].addr = mlx_get_data_addr(game->texture[i].img,
				&game->texture[i].bpp, &game->texture[i].line_len,
				&game->texture[i].endian);
		i++;
	}
	return ;
}
