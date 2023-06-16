/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:35:02 by valentin          #+#    #+#             */
/*   Updated: 2023/06/16 23:43:53 by valentin         ###   ########.fr       */
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
	return ;
}

int	copy_map_bis(int j, int i, t_data *game, char **str)
{
	int	d;

	d = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != ' ' && str[i][j] != '1' && str[i][j] != '0'
				&& str[i][j] != 'N' && str[i][j] != 'W' && str[i][j] != 'S'
					&& str[i][j] != 'E')
				return (-1);
			if ((str[i][j] == 'N' || str[i][j] == 'W' || str[i][j] == 'S'
				|| str[i][j] == 'E') && check_close(str, j, i))
			{
				set_pos_player(str[i][j], i, j, game);
				d++;
			}
			j++;
		}
		i++;
	}
	if (d != 1)
		return (write(2, "Error : one player position needed\n", 36), -1);
	return (i);
}

int	copy_map(char **str, t_data *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = copy_map_bis(j, i, game, str);
	if (i == -1)
		return (0);
	game->map = malloc(sizeof(char *) * (i + 1));
	if (!game->map)
		return (0);
	i = 0;
	while (str[i])
	{
		game->map[i] = ft_strdup(str[i]);
		i++;
	}
	game->map[i] = NULL;
	if (!check_wall_map(game->map))
		return (write(2, "Error : map not close\n", 23), 0);
	return (1);
}
