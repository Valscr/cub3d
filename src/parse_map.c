/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:15:15 by valentin          #+#    #+#             */
/*   Updated: 2023/06/14 23:40:02 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <stdio.h>

int	ft_strlen_less_returnline(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (str[i] == '\n')
		i--;
	return (i);
}

int	check_double_return_line(char *str)
{
	int	i;

	i = ft_strlen_less_returnline(str);
	while (i > 0)
	{
		if (str[i] == 'F' || str[i] == 'C' || (str[i] == 'N'
				&& str[i + 1] == 'O') || (str[i] == 'S'
				&& str[i + 1] == 'O') || (str[i] == 'W'
				&& str[i + 1] == 'E') || (str[i] == 'E' && str[i + 1] == 'A'))
		{
			while (str[i] != '\n')
				i++;
			while (str[i] != '1')
				i++;
			while (i < ft_strlen_less_returnline(str))
			{
				if (str[i] == '\n' && str[i + 1] == '\n')
					return (0);
				i++;
			}
			return (1);
		}
		i--;
	}
	return (0);
}

int	parse_map_true(char **str, t_data *game)
{
	int	i;

	i = 6;
	while (str[i])
	{
		if (str[i][0] != 'N' && str[i][0] != 'S' && str[i][0] != 'E'
			&& str[i][0] != 'W' && str[i][0] != 'F' && str[i][0] != 'C'
				&& find_one(str[i]))
		{
			if (!copy_map(&str[i], game))
				return (0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	parse_map(int fd, t_data *game)
{
	char	*str;
	char	**full;
	int		i;

	i = 0;
	str = get_next_line(fd);
	if (str == 0)
	{
		write(2, "Error : Empty file\n", 20);
		return (0);
	}
	if (!check_double_return_line(str))
		return (free_str(str), write(2, "Error : map not close\n", 23), 0);
	full = ft_split(str, '\n');
	free(str);
	if (!parse_map_texture_color(full, game))
		return (free_tab_str(full), write(2,
				"Error : missing infos .cub file\n", 33), 0);
	while (i < 4)
		if (!is_xpm_file(game->name_texture[i++]))
			return (free_tab_str(full), 0);
	if (!parse_map_true(full, game))
		return (free_tab_str(full), write(2, "Error : bad map format\n", 23), 0);
	return (free_tab_str(full), 1);
}

int	set_map(char **str, t_data *game)
{
	int		fd;

	game->map = NULL;
	if (!find_extension(str[1], ".cub"))
	{
		write(2, "Error : No correct format map finded (.cub)\n", 45);
		return (1);
	}
	else
	{
		fd = open(str[1], O_RDONLY);
		if (fd > 0)
		{
			if (!parse_map(fd, game))
				return (1);
		}
		else
			return (write(2, "Error : file not found\n", 23), 1);
	}
	return (0);
}
