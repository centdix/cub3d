/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_bmp_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:05:19 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/29 13:24:30 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_write_half_int(int fd, unsigned int w)
{
	char byt;

	byt = w & 0xff;
	write(fd, &byt, 1);
	byt = (w >> 8) & 0xff;
	write(fd, &byt, 1);
}

void	ft_write_int(int fd, unsigned int w)
{
	ft_write_half_int(fd, w);
	ft_write_half_int(fd, w >> 16);
}

void	ft_write_color(int fd, unsigned int color)
{
	char byt;

	ft_write_half_int(fd, color);
	byt = (color >> 16) & 0xff;
	write(fd, &byt, 1);
}

void	ft_write_empty(int fd, int count)
{
	while (count)
	{
		write(fd, "\0", 1);
		count--;
	}
}
