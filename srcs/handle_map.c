/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 14:54:08 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/25 20:54:24 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	get_rotation(t_param *param, int i, int j)
{
	if ((param->map[i][j] + '0') == 'N')
		param->rotation = 0;
	else if ((param->map[i][j] + '0') == 'S')
		param->rotation = M_PI;
	else if ((param->map[i][j] + '0') == 'E')
		param->rotation = (M_PI_2);
	else if ((param->map[i][j] + '0') == 'W')
		param->rotation = -(M_PI_2);
}

static void	get_sp_pos(int width, int height, t_all *all)
{
	int i;
	int j;
	int k;

	if (!(all->sp = malloc(sizeof(t_sprite) * all->param.sprite_nbr)))
		return ;
	k = 0;
	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (all->param.map[i][j] == 2)
			{
				all->sp[k].pos_x = i;
				all->sp[k].pos_y = j;
				k++;
			}
			j++;
		}
		i++;
	}
}

void		handle_map(int width, int height, t_all *all)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (all->param.map[i][j] == 2)
				all->param.sprite_nbr++;
			if (ft_isdir(all->param.map[i][j] + '0'))
			{
				all->param.pos_x = i + 0.1;
				all->param.pos_y = j + 0.1;
				get_rotation(&all->param, i, j);
			}
			j++;
		}
		i++;
	}
	if (all->param.sprite_nbr > 0)
		get_sp_pos(width, height, all);
}
