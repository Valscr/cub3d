/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:16:50 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 18:17:54 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	find_int_bis(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		return (0);
	else
		return (1);
}

int	find_int(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] == ' ')
			i++;
		if (!ft_isdigit(str[i]))
			return (0);
		while (ft_isdigit(str[i]))
			i++;
		j++;
		while (str[i] == ' ')
			i++;
		if (j == 3)
			return (find_int_bis(str, i));
		if (str[i] != ',')
			return (0);
		i++;
	}
	return (0);
}

int	convert_hex(char *str)
{
	int			r;
	int			g;
	int			b;
	char		**string;

	if (!find_int(str))
		return (-1);
	string = ft_split2(str, " ,");
	r = ft_atoi(string[0]);
	g = ft_atoi(string[1]);
	b = ft_atoi(string[2]);
	return (convert_hex_bis(string, r, g, b));
}

int	convert_hex_bis(char **string, int r, int g, int b)
{
	char				*hexdigits;
	unsigned int		color;
	char				*hexcolor;
	int					i;

	hexdigits = ft_strdup("0123456789ABCDEF");
	color = (r << 16) | (g << 8) | b;
	hexcolor = malloc(sizeof(char) * 7);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_tab_str(string), free(hexdigits), free(hexcolor), -1);
	hexcolor[6] = '\0';
	i = 5;
	while (i >= 0)
	{
		hexcolor[i--] = hexdigits[color & 0xF];
		color >>= 4;
	}
	return (free_tab_str(string), free(hexdigits),
		ft_atoi_base(hexcolor, "0123456789ABCDEF"));
}

int	parse_map_texture_color(char **str, t_data *game)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] == 'N' && str[i][1] == 'O' && str[i][2] == ' ')
			game->name_texture[0] = put_image_file(&str[i][3]);
		else if (str[i][0] == 'S' && str[i][1] == 'O' && str[i][2] == ' ')
			game->name_texture[1] = put_image_file(&str[i][3]);
		else if (str[i][0] == 'W' && str[i][1] == 'E' && str[i][2] == ' ')
			game->name_texture[2] = put_image_file(&str[i][3]);
		else if (str[i][0] == 'E' && str[i][1] == 'A' && str[i][2] == ' ')
			game->name_texture[3] = put_image_file(&str[i][3]);
		else if (str[i][0] == 'F' && str[i][1] == ' ')
			game->color_floor = convert_hex(&str[i][2]);
		else if (str[i][0] == 'C' && str[i][1] == ' ')
			game->color_ceiling = convert_hex(&str[i][2]);
		i++;
	}
	if (game->color_floor == -1 || game->color_ceiling == -1
		|| game->name_texture[0] == NULL || game->name_texture[1] == NULL
		|| game->name_texture[2] == NULL || game->name_texture[3] == NULL)
		return (0);
	return (1);
}
