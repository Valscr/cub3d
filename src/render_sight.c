/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sight.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 22:55:50 by valentin          #+#    #+#             */
/*   Updated: 2023/06/01 22:56:15 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_sight_hrz(t_img *img)
{
	int	i;
	int	j;
	int	d;

	i = (WINDOW_HEIGHT / 8) * 3;
	j = (WINDOW_WIDTH / 8) * 3;
	d = 0;
	while (d < (WINDOW_WIDTH / 8) / 2)
	{
		img_pix_put(img, j++, i, GREEN_PIXEL);
		d++;
	}
	d = 0;
	j = (WINDOW_WIDTH / 8) * 5;
	while (d < (WINDOW_WIDTH / 8) / 2)
	{
		img_pix_put(img, j--, i, GREEN_PIXEL);
		d++;
	}
	return ;
}

void	render_sight_vrt(t_img *img)
{
	int	d;
	int	i;

	d = 0;
	i = (WINDOW_HEIGHT / 8) * 3;
	while (d < (WINDOW_WIDTH / 8) / 2)
	{
		img_pix_put(img, (WINDOW_WIDTH / 8) * 3, i, GREEN_PIXEL);
		img_pix_put(img, (WINDOW_WIDTH / 8) * 5, i, GREEN_PIXEL);
		i++;
		d++;
	}
	d = 0;
	i = (WINDOW_HEIGHT / 8) * 5;
	while (d < (WINDOW_WIDTH / 8) / 2)
	{
		img_pix_put(img, (WINDOW_WIDTH / 8) * 3, i, GREEN_PIXEL);
		img_pix_put(img, (WINDOW_WIDTH / 8) * 5, i, GREEN_PIXEL);
		i--;
		d++;
	}
	return ;
}

void	render_sight(t_img *img)
{
	int	i;
	int	j;
	int	d;

	render_sight_hrz(img);
	render_sight_vrt(img);
	i = (WINDOW_HEIGHT / 8) * 5;
	j = (WINDOW_WIDTH / 8) * 3;
	d = 0;
	while (d < (WINDOW_WIDTH / 8) / 2)
	{
		img_pix_put(img, j++, i, GREEN_PIXEL);
		d++;
	}
	d = 0;
	j = (WINDOW_WIDTH / 8) * 5;
	while (d < (WINDOW_WIDTH / 8) / 2)
	{
		img_pix_put(img, j--, i, GREEN_PIXEL);
		d++;
	}
	return ;
}
