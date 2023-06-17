/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parse_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 16:03:49 by valentin          #+#    #+#             */
/*   Updated: 2023/06/17 19:57:35 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	count_tab_full_lesspace(char **str, int j, int i)
{
	int	d;

	d = i;
	while (ft_strlen_lesspace(str[d]) <= j && d > 0)
		d--;
	while (ft_strlen(str[d]) > j && str[d][j] == ' ' && d > 0)
		d--;
	return (d);
}

int	check_close_x_left(char **str, int j, int i)
{
	while (j >= 0)
	{
		if (str[i][j] == '1')
			return (1);
		j--;
	}
	return (0);
}

int	check_close_x_right(char **str, int j, int i)
{
	while (j <= ft_strlen_lesspace(str[i]))
	{
		if (str[i][j] == '1')
			return (1);
		j++;
	}
	return (0);
}

int	check_close_y_left(char **str, int j, int i)
{
	while (i >= 0 && ft_strlen_lesspace(str[i]) >= j)
	{
		if (str[i][j] == '1')
			return (1);
		i--;
	}
	return (0);
}

int	check_close_y_right(char **str, int j, int i)
{
	while (i < count_tab_full(str) && ft_strlen_lesspace(str[i]) >= j)
	{
		if (str[i][j] == '1')
			return (1);
		i++;
	}
	return (0);
}
