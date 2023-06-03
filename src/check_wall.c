/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:25:05 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:21:11 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_tab(char **str, int x, int y)
{
	int	i;

	i = y;
	while (i >= 0)
	{
		if (str[i][x] == '1')
			return (i);
		i--;
	}
	return (i);
}

int	count_tab_full(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	count_x(char *str, int x)
{
	int	i;

	i = x / 100;
	while (i >= 0)
	{
		if (str[i] == '1')
			return (i);
		i--;
	}
	return (i);
}

int	check_wall(double x, double y, t_data *game)
{
	int	xindex;
	int	yindex;

	if (y < 0 || x < 0)
		return (1);
	yindex = (int)(y / 100.0);
	xindex = (int)(x / 100.0);
	if (fmod(y, 100.0) == 0.0)
	{
		if (((int)(y / 100.0)) > (count_tab(game->map, xindex,
			(int)(y / 100.0))))
			yindex = (int)(y / 100.0) - 1;
	}
	if (fmod(x, 100.0) == 0.0)
	{
		if ((int)(x / 100.0) > ((count_x(game->map[yindex], (int)x))))
			xindex = (int)(x / 100.0) - 1;
	}	
	if (yindex >= count_tab_full(game->map) || yindex < 0)
		return (1);
	if (xindex >= ft_strlen(game->map[yindex]) || xindex < 0)
		return (1);
	if (game->map[yindex][xindex] == '1')
		return (1);
	return (0);
}
