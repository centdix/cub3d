/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:28:43 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/26 18:19:40 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_rotate(t_all *all, double angle)
{
	double olddirx;
	double oldplanex;

	olddirx = all->posdir.dir_x;
	all->posdir.dir_x = all->posdir.dir_x * cos(angle)
						- all->posdir.dir_y * sin(angle);
	all->posdir.dir_y = olddirx * sin(angle)
						+ all->posdir.dir_y * cos(angle);
	oldplanex = all->posdir.plane_x;
	all->posdir.plane_x = all->posdir.plane_x * cos(angle)
						- all->posdir.plane_y * sin(angle);
	all->posdir.plane_y = oldplanex * sin(angle)
						+ all->posdir.plane_y * cos(angle);
}
