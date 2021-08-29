/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:03:08 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/24 18:03:28 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

int	iter_mandelbrot(double x, double y, t_pos *pos)
{
	int		i;
	double	z_r;
	double	z_i;
	double	z_r2;
	double	z_i2;

	i = 1;
	z_r = 0;
	z_i = 0;
	z_r2 = 0;
	z_i2 = 0;
	while (i < pos->iter_count && (z_r2 + z_i2) <= 4)
	{
		z_i = 2 * z_i * z_r + y;
		z_r = z_r2 - z_i2 + x;
		z_r2 = z_r * z_r;
		z_i2 = z_i * z_i;
		i++;
	}
	if (i == pos->iter_count)
		return (0);
	return (i);
}

void	mandelbrot_calculate_pixels(t_pos *pos, t_vars *vars)
{
	int		i;
	double	x;
	double	y;
	double	p;

	while (pos->pos_x < WIDTH)
	{
		while (pos->pos_y < HEIGHT)
		{
			x = (pos->pos_x - pos->width_adpt) / pos->zoom + pos->x1;
			y = (pos->pos_y - pos->height_adpt) / pos->zoom + pos->y1;
			p = sqrt(pow((x - (double)1 / 4), 2) + pow(y, 2));
			i = 0;
			if (pow(x + 1, 2) + pow(y, 2) > ((double)1 / 16)
				&& x > p - (2.8 * pow(p, 2) + (double)1 / 4))
				i = iter_mandelbrot(x, y, pos);
			if (i)
				img_pxl_put(&vars->img, WIDTH - pos->pos_x, pos->pos_y,
					encode_rgb(255 - i * 3, 255 - i * 15,
						fabs(sin((double)i * 4))));
			pos->pos_y++;
		}
		pos->pos_y = 0;
		pos->pos_x++;
	}
}

int	create_mandelbrot(t_pos *pos, t_vars *vars)
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
	mandelbrot_calculate_pixels(pos, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.mlx_img, 0, 0);
	ft_putstr("process ended successfully \n");
	return (1);
}

void	init_mandelbrot(t_pos *pos)
{
	pos->x1 = 0.6;
	pos->x2 = -2.1;
	pos->y1 = 1.2;
	pos->y2 = -1.2;
	pos->height_adpt = 0;
	pos->width_adpt = 0;
	pos->iter_multiplier = 1;
	pos->iter_count = 200;
	pos->set = 1;
	init_zoom(pos);
	window_adapt(pos);
	get_image(pos);
}

void	mandelbrot_set(void)
{
	t_vars	vars;
	t_pos	pos;
	t_all	all;
	t_img	img;

	init_img(&img);
	vars.img = img;
	init_mandelbrot(&pos);
	vars.mlx = mlx_init();
	if (vars.mlx == NULL)
		return ;
	vars.win = mlx_new_window(vars.mlx, WIDTH, HEIGHT, "Mandelbrot set");
	if (vars.win == NULL)
		return ;
	all.p = &pos;
	all.v = &vars;
	create_mandelbrot(&pos, &vars);
	mlx_mouse_hook(vars.win, mouse_pos, &all);
	mlx_hook(vars.win, 2, 1L << 0, close_window, &vars);
	mlx_hook(vars.win, 17, 0L, close_window_red_cross, &vars);
	mlx_loop(vars.mlx);
}
