/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 15:54:01 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/28 20:35:27 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_param(t_all *all)
{
	int i;

	all->param.screen_w = 0;
	all->param.screen_h = 0;
	i = 0;
	while (i < 4)
	{
		all->param.path_tex[i] = NULL;
		i++;
	}
	all->param.path_sp_tex = NULL;
	all->param.floor_color = 16777215;
	all->param.ceiling_color = 16777215;
	all->param.map_width = 0;
	all->param.map_height = 0;
	all->param.sprite_nbr = 0;
	all->param.pos_x = 0;
	all->param.pos_y = 0;
	all->param.rotation = -1;
}

static void	init_posdir(t_all *all)
{
	all->posdir.pos_x = all->param.pos_x;
	all->posdir.pos_y = all->param.pos_y;
	all->posdir.dir_x = -1;
	all->posdir.dir_y = 0;
	all->posdir.plane_x = 0;
	all->posdir.plane_y = 0.66;
	ft_rotate(all, all->param.rotation);
}

static void	init_loop(t_all *all)
{
	mlx_hook(all->data.mlx_win, 2, (1L << 0), get_key, all);
	mlx_hook(all->data.mlx_win, 17, 0, exit_game, all);
	mlx_loop(all->data.mlx_ptr);
}

int			main(int ac, char **av)
{
	t_all		all;

	init_param(&all);
	if (ac < 2 || get_param(&all, av[1]) == -1)
	{
		ft_putstr("Error\nInvalid or missing file");
		return (1);
	}
	if (has_error(&all))
		return (1);
	if (!(all.data.mlx_ptr = mlx_init()))
		return (1);
	if (!(all.data.mlx_win = mlx_new_window(all.data.mlx_ptr,
		all.param.screen_w, all.param.screen_h, "Cub3d")))
		return (1);
	if (!check_textures(&all))
		return (1);
	init_posdir(&all);
	render(&all);
	if (av[2] && ft_strlen(av[2]) == 5 && !ft_strncmp(av[2], "-save", 5))
		create_bmp("screen.bmp", &all);
	else
		init_loop(&all);
	return (0);
}
