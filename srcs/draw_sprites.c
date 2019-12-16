/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:46:11 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/26 18:16:49 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	do_sprite_math(t_dda *dda, t_all *all, int i)
{
	dda->sp_x = all->sp[i].pos_x - all->posdir.pos_x;
	dda->sp_y = all->sp[i].pos_y - all->posdir.pos_y;
	dda->inv = 1.0 / (all->posdir.plane_x * all->posdir.dir_y
						- all->posdir.dir_x * all->posdir.plane_y);
	dda->trans_x = dda->inv * (all->posdir.dir_y * dda->sp_x
					- all->posdir.dir_x * dda->sp_y);
	dda->trans_y = dda->inv * (-(all->posdir.plane_y) * dda->sp_x
							+ all->posdir.plane_x * dda->sp_y);
	dda->sp_screenx = (int)((all->param.screen_w / 2)
						* (1 + dda->trans_x / dda->trans_y));
	dda->sp_h = abs((int)(all->param.screen_h / (dda->trans_y))) / 2;
	dda->start_y = -(dda->sp_h) / 2 + all->param.screen_h / 2;
	if (dda->start_y < 0)
		dda->start_y = 0;
	dda->end_y = dda->sp_h / 2 + all->param.screen_h / 2;
	if (dda->end_y >= all->param.screen_h)
		dda->end_y = all->param.screen_h - 1;
	dda->sp_w = abs((int)(all->param.screen_h / (dda->trans_y))) / 2;
	dda->start_x = -(dda->sp_w) / 2 + dda->sp_screenx;
	if (dda->start_x < 0)
		dda->start_x = 0;
	dda->end_x = dda->sp_w / 2 + dda->sp_screenx;
	if (dda->end_x >= all->param.screen_w)
		dda->end_x = all->param.screen_w - 1;
}

static void	draw_them(t_dda *dda, t_all *all, int i, int stripe)
{
	int y;
	int d;
	int color;

	dda->sp_tex_x = (int)(256 * (stripe - (-(dda->sp_w) / 2 + dda->sp_screenx))
							* all->sp[i].xpm.width / dda->sp_w) / 256;
	if (dda->trans_y > 0 && stripe > 0 && stripe < all->param.screen_w
						&& dda->trans_y < dda->z_buf[stripe])
	{
		y = dda->start_y;
		while (y < dda->end_y)
		{
			d = (y) * 256 - all->param.screen_h * 128 + dda->sp_h * 128;
			dda->sp_tex_y = ((d * all->sp[i].xpm.height) / dda->sp_h) / 256;
			color = *(all->sp[i].xpm.data_ptr + (all->sp[i].xpm.width
						* dda->sp_tex_y) + dda->sp_tex_x);
			if ((color & 0x00FFFFFF) != 0)
				*(all->image.data_ptr + (all->param.screen_w * y)
							+ stripe) = color;
			y++;
		}
	}
}

static void	get_tex(t_all *all)
{
	int i;

	i = 0;
	while (i < all->param.sprite_nbr)
	{
		all->sp[i].xpm.ptr = mlx_xpm_file_to_image(all->data.mlx_ptr,
		all->param.path_sp_tex, &all->sp[i].xpm.width, &all->sp[i].xpm.height);
		all->sp[i].xpm.data_ptr = (int *)mlx_get_data_addr(all->sp[i].xpm.ptr,
			&all->sp[i].xpm.bpp, &all->sp[i].xpm.size, &all->sp[i].xpm.endian);
		all->sp[i].distance = ((all->posdir.pos_x - all->sp[i].pos_x)
			* (all->posdir.pos_x - all->sp[i].pos_x) + (all->posdir.pos_y
			- all->sp[i].pos_y) * (all->posdir.pos_y - all->sp[i].pos_y));
		i++;
	}
}

void		draw_sprites(t_dda *dda, t_all *all)
{
	int i;
	int stripe;

	get_tex(all);
	sort_sprite(all);
	i = 0;
	while (i < all->param.sprite_nbr)
	{
		do_sprite_math(dda, all, i);
		stripe = dda->start_x;
		while (stripe < dda->end_x)
		{
			draw_them(dda, all, i, stripe);
			stripe++;
		}
		i++;
	}
}
