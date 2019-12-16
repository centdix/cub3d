/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:23:03 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/26 18:23:07 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#define SPEED 0.5

void	ft_move_forward(t_all *all)
{
	if (all->param.map[(int)(all->posdir.pos_x + all->posdir.dir_x * SPEED)]
				[(int)(all->posdir.pos_y)] == 0)
		all->posdir.pos_x += all->posdir.dir_x * SPEED;
	if (all->param.map[(int)(all->posdir.pos_x)]
				[(int)(all->posdir.pos_y + all->posdir.dir_y * SPEED)] == 0)
		all->posdir.pos_y += all->posdir.dir_y * SPEED;
}

void	ft_move_backward(t_all *all)
{
	if (all->param.map[(int)(all->posdir.pos_x - all->posdir.dir_x * SPEED)]
				[(int)(all->posdir.pos_y)] == 0)
		all->posdir.pos_x -= all->posdir.dir_x * SPEED;
	if (all->param.map[(int)(all->posdir.pos_x)]
				[(int)(all->posdir.pos_y - all->posdir.dir_y * SPEED)] == 0)
		all->posdir.pos_y -= all->posdir.dir_y * SPEED;
}

void	ft_move_right(t_all *all)
{
	if (all->param.map[(int)(all->posdir.pos_x + all->posdir.plane_x * SPEED)]
				[(int)(all->posdir.pos_y)] == 0)
		all->posdir.pos_x += all->posdir.plane_x * SPEED;
	if (all->param.map[(int)(all->posdir.pos_x)]
				[(int)(all->posdir.pos_y + all->posdir.plane_y * SPEED)] == 0)
		all->posdir.pos_y += all->posdir.plane_y * SPEED;
}

void	ft_move_left(t_all *all)
{
	if (all->param.map[(int)(all->posdir.pos_x - all->posdir.plane_x * SPEED)]
				[(int)(all->posdir.pos_y)] == 0)
		all->posdir.pos_x -= all->posdir.plane_x * SPEED;
	if (all->param.map[(int)(all->posdir.pos_x)]
				[(int)(all->posdir.pos_y - all->posdir.plane_y * SPEED)] == 0)
		all->posdir.pos_y -= all->posdir.plane_y * SPEED;
}
