/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:03:47 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/23 21:25:56 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

int	iter_julia(double x, double y, t_pos *pos)
{
	int		i;
	double	z_r;
	double	z_i;
	double	tmp;

	i = 1;
	z_r = x;
	z_i = y;
	tmp = z_r;
	z_r = z_r * z_r - z_i * z_i + pos->c_r;
	z_i = 2 * z_i * tmp + pos->c_i;
	while (i < pos->iter_count && (z_r * z_r + z_i * z_i) <= 4)
	{
		tmp = z_r;
		z_r = z_r * z_r - z_i * z_i + pos->c_r;
		z_i = 2 * z_i * tmp + pos->c_i;
		i++;
	}
	if (i == pos->iter_count)
		return (0);
	return (i);
}

void	julia_calculate_pixels(t_pos *pos, t_vars *vars)
{
	int		i;
	double	x;
	double	y;

	i = 0;
	while (pos->pos_x < WIDTH)
	{
		while (pos->pos_y < HEIGHT)
		{
			x = (pos->pos_x - pos->width_adpt) / pos->zoom + pos->x1;
			y = (pos->pos_y - pos->height_adpt) / pos->zoom + pos->y1;
			i = iter_julia(x, y, pos);
			if (i)
				img_pxl_put(&vars->img, WIDTH - pos->pos_x, pos->pos_y,
					encode_rgb(255 - i * 3, 255 - i * 15,
						fabs(sin((double)i * 4))));
			pos->pos_y++;
			i = 0;
		}
		pos->pos_y = 0;
		pos->pos_x++;
	}
}

int	create_julia(t_pos *pos, t_vars *vars)
{
	pos->pos_x = 0;
	pos->pos_y = 0;
	vars->img.mlx_img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (vars->img.mlx_img == NULL)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		return (0);
	}
	vars->img.addr = mlx_get_data_addr(vars->img.mlx_img,
			&vars->img.bpp, &vars->img.line_len, &vars->img.endian);
	julia_calculate_pixels(pos, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.mlx_img, 0, 0);
	printf("process ended successfully \n");
	return (1);
}

void	init_julia(t_pos *pos, double c_r, double c_i)
{
	pos->x1 = -2;
	pos->x2 = 2;
	pos->y1 = -2;
	pos->y2 = 2;
	pos->height_adpt = 0;
	pos->width_adpt = 0;
	pos->iter_multiplier = 1;
	pos->iter_count = 200;
	pos->set = 2;
	pos->c_r = c_r;
	pos->c_i = c_i;
	init_zoom(pos);
	window_adapt(pos);
}

void	julia_set(double c_r, double c_i)
{
	t_vars	vars;
	t_pos	pos;
	t_all	all;
	t_img	img;

	init_img(&img);
	vars.img = img;
	init_julia(&pos, c_r, c_i);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return ;
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "test");
	if (vars.win == NULL)
		return ;
	all.p = &pos;
	all.v = &vars;
	get_image(&pos);
	create_julia(&pos, &vars);
	mlx_mouse_hook(vars.win, mouse_pos, &all);
	mlx_hook(vars.win, 2, 1L << 0, close_window, &vars);
	mlx_hook(vars.win, 17, 0L, close_window_red_cross, &vars);
	mlx_loop(vars.mlx);
}
