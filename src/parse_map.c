/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:15:15 by valentin          #+#    #+#             */
/*   Updated: 2023/05/31 18:49:20 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_pos_player(char c, int y, int x, t_data *game)
{
	if (c == 'N')
		game->angle = 180;
	else if (c == 'S')
		game->angle = 0;
	else if (c == 'W')
		game->angle = 270;
	else if (c == 'E')
		game->angle = 90;
	game->posy = y * 100 + 50;
	game->posx = x * 100 + 50;

	return;
}

int ft_strlen_lesspace(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] != ' ')
			return (i);
		i--;
	}
	return (i);
}

int	check_wall_map(char **str)
{
	int i;
	int j;

	i = 0;
	while (str[0][i])
	{
		if (str[0][i] == '0')
			return (0);
		i++;
	}
	i = 1;
	while (str[i + 1])
	{
		j = 0;
		while (str[i][j] == ' ')
			j++;
		if (str[i][j] != '1')
			return (0);
		while (j < ft_strlen_lesspace(str[i]))
		{
			if (str[i][j] == '0')
			{
				if (j > ft_strlen_lesspace(str[i - 1]) || j > ft_strlen_lesspace(str[i + 1]) || str[i - 1][j] == ' ' || str[i + 1][j] == ' ')
					return (0);
			}
			j++;
		}
		if (str[i][ft_strlen_lesspace(str[i])] == '0' || ft_strlen_lesspace(str[i]) == 0)
			return (0);
		i++;
	}
	while (str[i][j])
	{
		if (str[i][j] == '0')
			return (0);
		j++;
	}
	return (1);
}

int	ft_strlen_less_returnline(char *str)
{
	int i;

	i = ft_strlen(str) - 1;
	while (str[i] == '\n')
		i--;
	return (i);
}

int check_double_return_line(char *str)
{
	int i;

	i = ft_strlen_less_returnline(str);
	while (i > 0)
	{
		if (str[i] == 'F' || str[i] == 'C' || (str[i] == 'N' && str[i + 1] == 'O')
			|| (str[i] == 'S' && str[i + 1] == 'O')|| (str[i] == 'W' && str[i + 1] == 'E')
				|| (str[i] == 'E' && str[i + 1] == 'A'))
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

int	copy_map(char **str, t_data *game)
{
	int i;
	int j;
	int d;

	i = 0;
	d = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != ' ' && str[i][j] != '1' && str[i][j] != '0' && str[i][j] != 'N'
				&& str[i][j] != 'W' && str[i][j] != 'S' && str[i][j] != 'E')
				return (0);
			if (str[i][j] == 'N' || str[i][j] == 'W' || str[i][j] == 'S' || str[i][j] == 'E')
			{
				set_pos_player(str[i][j], i, j, game);
				d++;
			}
			j++;
		}
		i++;
	}
	game->map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (str[i])
	{
		game->map[i] = ft_strdup(str[i]);
		i++;
	}
	if (d != 1 )
		return (0);
	if (!check_wall_map(game->map))
		return (write(2, "Error : map not close\n", 23), 0);
	return (1);
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

int	parse_map_true(char **str, t_data *game)
{
	int i;

	i = 6;
	while (str[i])
	{
		if (str[i][0] != 'N' && str[i][0] != 'S' && str[i][0] != 'E' && str[i][0] != 'W'
			&& str[i][0] != 'F' && str[i][0] != 'C' && find_one(str[i]))
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

	str = get_next_line(fd);
	if (str == 0)
	{
		write(2, "Error : Empty file\n", 20);
		exit(0);
	}
	if (!check_double_return_line(str))
		return (write(2, "Error : map not close\n", 23), 0);
	full = ft_split(str, '\n');
	free(str);
	if (!parse_map_texture_color(full, game))
		return(write(2, "Error : missing informations .cub file\n", 39), 0);
	if (!parse_map_true(full, game))
		return (write(2, "Error : bad map format\n", 23), 0);
	return (1);
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
		{
			if (!parse_map(fd, game))
				return (1);
		}
		else
			return (write(2, "Error : empty map\n", 18), 1);
	}
	return (0);
}