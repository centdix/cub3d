/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:15:02 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/26 21:49:39 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		get_key(int key, t_all *all)
{
	double angle;

	angle = M_PI_4 / 8;
	if (key == KEY_W)
		ft_move_forward(all);
	if (key == KEY_S)
		ft_move_backward(all);
	if (key == KEY_A)
		ft_move_left(all);
	if (key == KEY_D)
		ft_move_right(all);
	if (key == KEY_RIGHT)
		ft_rotate(all, -angle);
	if (key == KEY_LEFT)
		ft_rotate(all, angle);
	if (key == KEY_SPACE)
		ft_shoot(all);
	if (key == KEY_ESC)
		return (exit_game(all));
	mlx_clear_window(all->data.mlx_ptr, all->data.mlx_win);
	render(all);
	return (1);
}

int		exit_game(t_all *all)
{
	int i;

	i = 0;
	while (i < all->param.map_height)
	{
		free(all->param.map[i]);
		i++;
	}
	free(all->param.map);
	i = 0;
	while (i < 4)
	{
		free(all->param.path_tex[i]);
		i++;
	}
	if (all->param.path_sp_tex)
		free(all->param.path_sp_tex);
	if (all->param.sprite_nbr > 0)
		free(all->sp);
	mlx_destroy_window(all->data.mlx_ptr, all->data.mlx_win);
	exit(0);
}
