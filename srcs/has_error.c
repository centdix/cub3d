/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 16:34:49 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/27 20:14:22 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_sp_tex(t_all *all)
{
	void	*xpm;
	int		width;
	int		height;

	if (all->param.sprite_nbr > 0)
	{
		if (!(xpm = mlx_xpm_file_to_image(all->data.mlx_ptr,
				all->param.path_sp_tex, &width, &height)))
		{
			ft_putstr("Error\nCan't load textures");
			return (0);
		}
		else
			mlx_destroy_image(all->data.mlx_ptr, xpm);
	}
	return (1);
}

int			check_textures(t_all *all)
{
	void	*xpm;
	int		width;
	int		height;
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!(xpm = mlx_xpm_file_to_image(all->data.mlx_ptr,
				all->param.path_tex[i], &width, &height)))
		{
			ft_putstr("Error\nCan't load textures");
			return (0);
		}
		else
			mlx_destroy_image(all->data.mlx_ptr, xpm);
		i++;
	}
	if (!check_sp_tex(all))
		return (0);
	return (1);
}

static int	check_map(t_all *all)
{
	int i;

	if (all->param.map_width < 3 || all->param.map_height < 3)
		return (0);
	i = 0;
	while (i < all->param.map_width)
	{
		if (all->param.map[0][i] != 1)
			return (0);
		if (all->param.map[all->param.map_height - 1][i] != 1)
			return (0);
		i++;
	}
	i = 0;
	while (i < all->param.map_height)
	{
		if (all->param.map[i][0] != 1)
			return (0);
		if (all->param.map[i][all->param.map_width - 1] != 1)
			return (0);
		i++;
	}
	return (1);
}

static int	check_player(t_all *all)
{
	if (!all->param.pos_x || !all->param.pos_y)
		return (0);
	if (all->param.rotation == -1)
		return (0);
	return (1);
}

int			has_error(t_all *all)
{
	if (all->param.screen_w <= 0 || all->param.screen_h <= 0)
	{
		ft_putstr("Error\nInvalid or missing window resolution");
		return (1);
	}
	if (!check_map(all))
	{
		ft_putstr("Error\nInvalid map");
		return (1);
	}
	if (!check_player(all))
	{
		ft_putstr("Error\nInvalid or missing player position");
		return (1);
	}
	return (0);
}
