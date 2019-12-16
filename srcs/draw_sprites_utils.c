/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 20:56:21 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/25 21:04:51 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	swap(t_all *all, int i, int j)
{
	t_sprite	tmp;

	tmp = all->sp[i];
	all->sp[i] = all->sp[j];
	all->sp[j] = tmp;
}

void		sort_sprite(t_all *all)
{
	int gap;
	int swapped;
	int i;

	gap = all->param.sprite_nbr;
	swapped = 0;
	while (gap > 1 || swapped)
	{
		gap = (gap * 10) / 13;
		if (gap == 9 || gap == 10)
			gap = 11;
		if (gap < 1)
			gap = 1;
		swapped = 0;
		i = 0;
		while (i < all->param.sprite_nbr - gap)
		{
			if (all->sp[i].distance < all->sp[i + gap].distance)
			{
				swap(all, i, i + gap);
				swapped = 1;
			}
			i++;
		}
	}
}
