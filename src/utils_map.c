/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:06:38 by valentin          #+#    #+#             */
/*   Updated: 2023/06/16 16:07:53 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_close_close(char **str, int j, int i)
{
	int	x;

	x = j;
	while (x >= 0)
	{
		if (str[i][x] == '1')
			break ;
		if (str[i][x] == '0')
			return (0);
		x--;
	}
	while (j < ft_strlen(str[i]))
	{
		if (str[i][j] == '1')
			break ;
		if (str[i][j] == '0')
			return (0);
		j++;
	}
	return (1);
}

int	check_close(char **str, int j, int i)
{
	int	d;

	d = 0;
	if ((i <= count_y_space(str, j, i) - 1 && str[i][j] == ' '
		&& check_close_close(str, j, i))
		|| (i >= count_tab_full_lesspace(str, j, i) + 1
			&& str[i][j] == ' ' && check_close_close(str, j, i)))
		return (1);
	d += check_close_x_left(str, j, i);
	d += check_close_x_right(str, j, i);
	d += check_close_y_left(str, j, i);
	d += check_close_y_right(str, j, i);
	if (d == 4)
		return (1);
	return (0);
}

int	check_close_all(char **str, int j, int i)
{
	int	d;

	d = 0;
	d += check_close_x_left(str, j, i);
	d += check_close_x_right(str, j, i);
	d += check_close_y_left(str, j, i);
	d += check_close_y_right(str, j, i);
	if (d == 4)
		return (1);
	return (0);
}
