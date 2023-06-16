/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 17:30:35 by valentin          #+#    #+#             */
/*   Updated: 2023/06/16 16:08:30 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_wall_first_last(char **str)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (j < ft_strlen_lesspace(str[i]))
	{
		if (str[i][j] != '1' && str[i][j] != ' ')
			return (0);
		j++;
	}
	j = 0;
	i = count_tab_full(str) - 1;
	while (j < ft_strlen_lesspace(str[i]))
	{
		if (str[i][j] != '1' && str[i][j] != ' ')
			return (0);
		j++;
	}
	return (1);
}

int	count_y_space(char **str, int j, int i)
{
	int	d;

	d = i;
	while (str[d] && ft_strlen(str[d]) > j && str[d][j] == ' ')
		d++;
	return (d);
}

int	check_wall_map_bis(char **str, int i, int j)
{
	while (j < ft_strlen_lesspace(str[i]))
	{
		if (str[i][j] == '0' || str[i][j] == ' ')
		{
			if (!check_close(str, j, i))
				return (0);
		}
		j++;
	}
	return (1);
}

int	check_wall_map(char **str)
{
	int	i;
	int	j;

	if (!check_wall_first_last(str))
		return (0);
	i = 1;
	while (str[i + 1])
	{
		j = 0;
		while (str[i][j] == ' ')
			j++;
		if (str[i][j] != '1')
			return (0);
		if (!check_wall_map_bis(str, i, j))
			return (0);
		if (str[i][ft_strlen_lesspace(str[i])] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	ft_strlen_lesspace(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0)
	{
		if (str[i] != ' ')
			return (i);
		i--;
	}
	return (i);
}
