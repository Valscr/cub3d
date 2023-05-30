/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:25:05 by valentin          #+#    #+#             */
/*   Updated: 2023/05/30 13:25:26 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

int	count_tab_full(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	count_x(char *str, int x)
{
	int	i;

	i = x / 100;
	i++;
	if (str[i] == '1')
		return (i);
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

	if (y / 100 >= count_tab_full(game->map))
		return (1);
	if (x / 100 >= ft_strlen(game->map[(int)y / 100]))
		return (1);
	if (x <= ((count_x(game->map[(int)y / 100], (int)x) - 1) * 100))
		xIndex = (int)ceil((double)x / 100.0);
	else
		xIndex = x / 100.0;

	if (y <= (count_tab(game->map, (int)x, (int)y) - 1) * 100)
		yIndex = (int)ceil((double)y / 100.0);
	else
		yIndex = y / 100.0;
	if (yIndex >= count_tab_full(game->map))
		return (1);
	if (xIndex >= ft_strlen(game->map[yIndex]))
		return (1);
	if (game->map[yIndex][xIndex] == '1')
	{
		if (fmod(x, 100.0) != 0 && fmod(y, 10.00) != 0)
			return (0);
		else
			return (1);
	}
	return (0);
}