/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 13:16:50 by valentin          #+#    #+#             */
/*   Updated: 2023/05/30 13:17:48 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int find_int(char *str)
{
	int i;
	int j;

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
		{
			while (str[i] == ' ')
				i++;
			if (str[i] != '\0')
				return (0);
			else
				return (1);
		}
		if (str[i] != ',')
			return (0);
		i++;
	}
	return (0);
}

int convertToHex(char *str)
{
    char *hexDigits;
 	unsigned int color;
    char* hexColor;
	char **string;
	int i;
	int r;
	int g;
	int b;

	if (!find_int(str))
		return (-1);
	string = ft_split2(str, " ,");
	r = ft_atoi(string[0]);
	g = ft_atoi(string[1]);
	b = ft_atoi(string[2]);
	hexDigits = ft_strdup("0123456789ABCDEF");
	color = (r << 16) | (g << 8) | b;
	hexColor = (char*)malloc(6 * sizeof(char));
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
    hexColor[6] = '\0';
	i = 5;
	while (i >= 0) 
	{
        hexColor[i--] = hexDigits[color & 0xF];
        color >>= 4;
    }
	return (free_tab_str(string), free(hexDigits),ft_atoi_base(hexColor, "0123456789ABCDEF"));
}

char	*put_image_file(char *str)
{
	int i;
	char *string;

	i = 0;
	string = NULL;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (NULL);
	string = ft_strdup(&str[i]);
	return (string);
}

int	parse_map_texture_color(char **str, t_data *game)
{
	int i;

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
			game->color_floor = convertToHex(&str[i][2]);
		else if (str[i][0] == 'C' && str[i][1] == ' ')
			game->color_ceiling = convertToHex(&str[i][2]);
		i++;
	}
	if (game->color_floor == -1 || game->color_ceiling == -1 || game->name_texture[0] == NULL
		|| game->name_texture[1] == NULL || game->name_texture[2] == NULL || game->name_texture[3] == NULL)
		return (0);
	return (1);
}