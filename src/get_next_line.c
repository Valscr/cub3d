/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 18:19:24 by vescaffr          #+#    #+#             */
/*   Updated: 2022/08/22 00:17:17 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

char	*get_next(char *save, int fd)
{
	int			bytes;
	char		*dest;

	dest = malloc(sizeof(char) * (3000));
	if (!dest)
		return (0);
	bytes = 1;
	bytes = read(fd, dest, 3000);
	if (bytes == -1)
	{
		free(dest);
		return (NULL);
	}
	dest[bytes] = '\0';
	save = ft_strjoin1(save, dest);
	return (save);
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*line;

	if (fd <= 0)
		return (0);
	save = get_next(save, fd);
	if (save == NULL)
		return (NULL);
	line = ft_cut_dest(save);
	free(save);
	return (line);
}

/*int	main(void)
{
	int	fd1;
	int	fd2;
	int	fd3;
	int	fd4;
	int	fd5;
	int	fd6;

	fd1 = open("test.txt", O_RDONLY);
	fd2 = open("test.txt", O_RDONLY);
	fd3 = open("test.txt", O_RDONLY);
	fd4 = open("test.txt", O_RDONLY);
	fd5 = open("test.txt", O_RDONLY);
	fd6 = open("test.txt", O_RDONLY);

	printf("%s", get_next_line(fd1));
	printf("%s", get_next_line(fd2));
	printf("%s", get_next_line(fd3));
	printf("%s", get_next_line(fd4));
	printf("%s", get_next_line(fd5));
	printf("%s", get_next_line(fd6));
	return (0);
}*/
