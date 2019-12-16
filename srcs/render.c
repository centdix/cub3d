/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 15:50:05 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/27 14:36:30 by fgoulama         ###   ########.fr       */
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

static void	find_side(t_dda *dda)
{
	if (dda->side_x < dda->side_y)
	{
		if (dda->ray_dx < 0)
			dda->side = 0;
		else if (dda->ray_dx > 0)
			dda->side = 1;
	}
	else
	{
		if (dda->ray_dy < 0)
			dda->side = 2;
		else if (dda->ray_dy > 0)
			dda->side = 3;
	}
}

static void	main_dda(t_dda *dda, t_posdir *posdir, int **map)
{
	dda->hit = 0;
	while (dda->hit == 0)
	{
		find_side(dda);
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
		if (map[dda->map_x][dda->map_y] == 1)
			dda->hit = 1;
	}
	if (dda->side == 0 || dda->side == 1)
		dda->perp_dist = (dda->map_x - posdir->pos_x + (1 - dda->step_x) / 2)
							/ dda->ray_dx;
	else
		dda->perp_dist = (dda->map_y - posdir->pos_y + (1 - dda->step_y) / 2)
							/ dda->ray_dy;
}

static void	do_the_math(t_all *all)
{
	t_dda	dda;
	int		x;

	x = 0;
	if (!(dda.z_buf = malloc(sizeof(double) * all->param.screen_w)))
		return ;
	while (x++ < all->param.screen_w)
	{
		dda.cam_x = 2 * x / (double)(all->param.screen_w) - 1;
		dda.ray_dx = all->posdir.dir_x + all->posdir.plane_x * dda.cam_x;
		dda.ray_dy = all->posdir.dir_y + all->posdir.plane_y * dda.cam_x;
		dda.map_x = (int)all->posdir.pos_x;
		dda.map_y = (int)all->posdir.pos_y;
		dda.delta_x = fabs(1 / dda.ray_dx);
		dda.delta_y = fabs(1 / dda.ray_dy);
		find_step(&dda, &all->posdir);
		main_dda(&dda, &all->posdir, all->param.map);
		draw(&dda, all, x);
		dda.z_buf[x] = dda.perp_dist;
	}
	if (all->param.sprite_nbr > 0)
		draw_sprites(&dda, all);
	free(dda.z_buf);
	draw_weapon(all, all->param.screen_w / 2 - (all->param.screen_w / 5) / 2,
					all->param.screen_h - (all->param.screen_h / (5 / 2)));
}

void		render(t_all *all)
{
	t_image	image;
	int		i;

	image.ptr = mlx_new_image(all->data.mlx_ptr, all->param.screen_w,
												all->param.screen_h);
	image.data_ptr = (int *)mlx_get_data_addr(image.ptr, &image.bpp,
											&image.size, &image.endian);
	all->weapon.ptr = mlx_xpm_file_to_image(all->data.mlx_ptr,
			"textures/img2.xpm", &all->weapon.width, &all->weapon.height);
	all->weapon.data_ptr = (int *)mlx_get_data_addr(all->weapon.ptr,
			&all->weapon.bpp, &all->weapon.size, &all->weapon.endian);
	i = 0;
	while (i < 4)
	{
		all->xpm[i].ptr = mlx_xpm_file_to_image(all->data.mlx_ptr,
			all->param.path_tex[i], &all->xpm[i].width, &all->xpm[i].height);
		all->xpm[i].data_ptr = (int *)mlx_get_data_addr(all->xpm[i].ptr,
			&all->xpm[i].bpp, &all->xpm[i].size, &all->xpm[i].endian);
		i++;
	}
	all->image = image;
	do_the_math(all);
	mlx_put_image_to_window(all->data.mlx_ptr, all->data.mlx_win,
							image.ptr, 0, 0);
}
