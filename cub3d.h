/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgoulama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:27:00 by fgoulama          #+#    #+#             */
/*   Updated: 2019/11/29 13:24:26 by fgoulama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"
# include "srcs/get_next_line.h"
# define KEY_W 13
# define KEY_D 2
# define KEY_A 0
# define KEY_S 1
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_ESC 53
# define KEY_SPACE 49

typedef struct	s_data
{
	void	*mlx_ptr;
	void	*mlx_win;
}				t_data;

typedef struct	s_param
{
	int		screen_w;
	int		screen_h;
	char	*path_tex[4];
	char	*path_sp_tex;
	int		floor_color;
	int		ceiling_color;
	int		map_width;
	int		map_height;
	int		**map;
	int		sprite_nbr;
	double	pos_x;
	double	pos_y;
	double	rotation;
}				t_param;

typedef struct	s_image
{
	void	*ptr;
	int		*data_ptr;
	int		bpp;
	int		size;
	int		endian;
}				t_image;

typedef struct	s_xpm
{
	void	*ptr;
	int		*data_ptr;
	int		width;
	int		height;
	int		bpp;
	int		size;
	int		endian;
}				t_xpm;

typedef struct	s_sprite
{
	t_xpm	xpm;
	int		pos_x;
	int		pos_y;
	int		height;
	int		width;
	double	distance;
}				t_sprite;

typedef struct	s_posdir
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}				t_posdir;

typedef struct	s_dda
{
	double	cam_x;
	double	ray_dx;
	double	ray_dy;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	double	perp_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		start;
	int		end;
	double	wall_x;
	int		tex_x[4];
	int		tex_y[4];
	double	sp_x;
	double	sp_y;
	double	inv;
	double	trans_x;
	double	trans_y;
	int		sp_screenx;
	int		sp_h;
	int		start_y;
	int		end_y;
	int		sp_w;
	int		start_x;
	int		end_x;
	int		sp_tex_x;
	int		sp_tex_y;
	double	*z_buf;
}				t_dda;

typedef struct	s_all
{
	t_data		data;
	t_param		param;
	t_posdir	posdir;
	t_image		image;
	t_xpm		xpm[4];
	t_sprite	*sp;
	t_xpm		weapon;
}				t_all;

typedef struct	s_pixel
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
}				t_pixel;

int				ft_isdir(int c);
int				get_param(t_all *all, char *file);
int				check_file(char *file);
char			*parse_map(int fd, char *line);
void			get_map(t_all *all, char *char_map);
void			handle_map(int width, int height, t_all *all);
int				check_textures(t_all *all);
int				has_error(t_all *all);
void			get_color(t_param *param, char *line, int id);
int				rgb_to_decimal(char *line);
int				get_key(int key, t_all *all);
int				exit_game(t_all *all);
void			ft_move_forward(t_all *all);
void			ft_move_backward(t_all *all);
void			ft_move_left(t_all *all);
void			ft_move_right(t_all *all);
void			ft_rotate(t_all *all, double angle);
void			ft_shoot(t_all *all);
void			draw(t_dda *dda, t_all *all, int x);
void			sort_sprite(t_all *all);
void			draw_sprites(t_dda *dda, t_all *all);
void			draw_weapon(t_all *all, int x, int y);
void			render(t_all *all);
void			create_bmp(char *filename, t_all *all);
void			ft_write_half_int(int fd, unsigned int w);
void			ft_write_int(int fd, unsigned int w);
void			ft_write_color(int fd, unsigned int color);
void			ft_write_empty(int fd, int count);

#endif
