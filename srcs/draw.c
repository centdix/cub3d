/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:47:25 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/26 17:46:25 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	pick_tex(t_dda *dda, t_all *all, int d, int *color)
{
	if (dda->side == 0)
	{
		dda->tex_y[0] = ((d * all->xpm[0].height) / dda->line_h) / 256;
		*color = *(all->xpm[0].data_ptr + (all->xpm[0].height * dda->tex_y[0])
								+ dda->tex_x[0]);
	}
	else if (dda->side == 1)
	{
		dda->tex_y[1] = ((d * all->xpm[1].height) / dda->line_h) / 256;
		*color = *(all->xpm[1].data_ptr + (all->xpm[1].height * dda->tex_y[1])
								+ dda->tex_x[1]);
	}
	else if (dda->side == 2)
	{
		dda->tex_y[3] = ((d * all->xpm[3].height) / dda->line_h) / 256;
		*color = *(all->xpm[3].data_ptr + (all->xpm[3].height * dda->tex_y[3])
								+ dda->tex_x[3]);
	}
	else if (dda->side == 3)
	{
		dda->tex_y[2] = ((d * all->xpm[2].height) / dda->line_h) / 256;
		*color = *(all->xpm[2].data_ptr + (all->xpm[2].height * dda->tex_y[2])
								+ dda->tex_x[2]);
	}
}

static void	draw_wall(t_dda *dda, t_all *all, int x)
{
	int j;
	int d;
	int color;

	j = dda->start;
	while (j < dda->end)
	{
		d = j * 256 - all->param.screen_h * 128 + dda->line_h * 128;
		pick_tex(dda, all, d, &color);
		*(all->image.data_ptr + (all->param.screen_w * j) + x) = color;
		j++;
	}
}

static void	draw_fl_cl(t_dda *dda, t_all *all, int x)
{
	int j;

	j = dda->end + 1;
	while (j < all->param.screen_h)
	{
		*(all->image.data_ptr + (all->param.screen_w * j)
			+ x) = all->param.floor_color;
		*(all->image.data_ptr + (all->param.screen_w
			* (all->param.screen_h - j) + x)) = all->param.ceiling_color;
		j++;
	}
}

void		draw(t_dda *dda, t_all *all, int x)
{
	int i;

	dda->line_h = (int)(all->param.screen_h / dda->perp_dist);
	dda->start = -(dda->line_h) / 2 + all->param.screen_h / 2;
	if (dda->start < 0)
		dda->start = 0;
	dda->end = dda->line_h / 2 + all->param.screen_h / 2;
	if (dda->end >= all->param.screen_h)
		dda->end = all->param.screen_h - 1;
	if (dda->side == 0 || dda->side == 1)
		dda->wall_x = all->posdir.pos_y + dda->perp_dist * dda->ray_dy;
	else
		dda->wall_x = all->posdir.pos_x + dda->perp_dist * dda->ray_dx;
	dda->wall_x -= floor((dda->wall_x));
	i = 0;
	while (i < 4)
	{
		dda->tex_x[i] = (int)(dda->wall_x * (double)(all->xpm[i].width));
		dda->tex_x[i] = all->xpm[i].width - dda->tex_x[i] - 1;
		i++;
	}
	draw_wall(dda, all, x);
	draw_fl_cl(dda, all, x);
}
