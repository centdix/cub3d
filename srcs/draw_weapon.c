/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:31:57 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/27 14:41:47 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_weapon(t_all *all, int x, int y)
{
	int i;
	int j;
	int tex;
	int tey;
	int color;

	i = 0;
	while (i < all->param.screen_w / 5)
	{
		tex = (int)(i * all->weapon.width / (all->param.screen_w / 5));
		j = 0;
		while (j < all->param.screen_h / (5 / 2))
		{
			tey = (int)(j * all->weapon.height
					/ (all->param.screen_h / (5 / 2)));
			color = *(all->weapon.data_ptr + (all->weapon.width * tey) + tex);
			if (color != 16777215)
				*(all->image.data_ptr
				+ (all->param.screen_w * (y + j)) + (x + i)) = color;
			j++;
		}
		i++;
	}
}
