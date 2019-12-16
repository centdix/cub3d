/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shoot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:29:06 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/26 21:47:57 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	find_step(t_dda *dda, t_posdir *posdir)
{
	if (dda->ray_dx < 0)
	{
		dda->step_x = -1;
		dda->side_x = (posdir->pos_x - dda->map_x) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (dda->map_x + 1.0 - posdir->pos_x) * dda->delta_x;
	}
	if (dda->ray_dy < 0)
	{
		dda->step_y = -1;
		dda->side_y = (posdir->pos_y - dda->map_y) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (dda->map_y + 1.0 - posdir->pos_y) * dda->delta_y;
	}
}

static void	main_dda(t_dda *dda, int **map)
{
	dda->hit = 0;
	while (dda->hit == 0)
	{
		if (dda->side_x < dda->side_y)
		{
			dda->side_x += dda->delta_x;
			dda->map_x += dda->step_x;
		}
		else
		{
			dda->side_y += dda->delta_y;
			dda->map_y += dda->step_y;
		}
		if (map[dda->map_x][dda->map_y] == 2)
		{
			dda->hit = 1;
			map[dda->map_x][dda->map_y] = 0;
		}
		else if (map[dda->map_x][dda->map_y] == 1)
			dda->hit = 2;
	}
}

void		ft_shoot(t_all *all)
{
	t_dda	dda2;

	dda2.ray_dx = all->posdir.dir_x;
	dda2.ray_dy = all->posdir.dir_y;
	dda2.map_x = (int)all->posdir.pos_x;
	dda2.map_y = (int)all->posdir.pos_y;
	dda2.delta_x = fabs(1 / dda2.ray_dx);
	dda2.delta_y = fabs(1 / dda2.ray_dy);
	find_step(&dda2, &all->posdir);
	main_dda(&dda2, all->param.map);
	if (dda2.hit == 1)
		all->param.sprite_nbr--;
}
