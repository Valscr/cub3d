/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:06:22 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/21 03:25:19 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlen1(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	check_end(char *dest)
{
	int	j;

	j = 0;
	if (!dest)
		return (1);
	while (dest[j] != '\0')
	{
		if (dest[j] == '\n')
			return (0);
		j++;
	}
	return (1);
}

char	*ft_strjoin1(char *s1, char *s2)
{
	int		size;
	int		i;
	char	*dest;
	int		j;

	i = 0;
	size = ft_strlen1(s1) + ft_strlen1(s2) + 1;
	dest = malloc(sizeof(char) * size);
	if (!dest || !s2)
		return (NULL);
	if (s1 != NULL)
	{
		while (s1[i] != '\0')
		{	
			dest[i] = s1[i];
			i++;
		}
	}
	j = 0;
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	free(s2);
	return (dest);
}

char	*ft_cut_dest(char *dest)
{
	char	*s;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!dest[i])
		return (NULL);
	while (dest[i] != '\0')
		i++;
	s = malloc(sizeof(char) * i + 1);
	while (j < i)
	{
		s[j] = dest[j];
		j++;
	}
	if (dest[j] == '\n')
	{
		s[j] = dest[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

char	*new_save(char *dest)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (dest[i] && dest[i] != '\n')
		i++;
	if (!dest[i])
	{
		free(dest);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen1(dest) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (dest[i])
		str[j++] = dest[i++];
	str[j] = '\0';
	free(dest);
	return (str);
}
