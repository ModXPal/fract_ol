/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:06:29 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/12 01:15:17 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

void	zoom_in(t_pos *pos)
{
	double	x_zoom;
	double	y_zoom;

	pos->iter_multiplier++;
	if (pos->iter_multiplier % 20 == 0)
		pos->iter_count += 200 * 1.8;
	printf("iter_multiplier = %d \n", pos->iter_multiplier);
	printf("iter_count = %d \n", pos->iter_count);
	x_zoom = pos->delta_x - pos->delta_x * 0.90;
	y_zoom = pos->delta_y - pos->delta_y * 0.90;
	pos->x1 = pos->x1 + x_zoom * pos->mouse_x1;
	pos->x2 = pos->x2 - x_zoom * pos->mouse_x2;
	pos->y1 = pos->y1 + y_zoom * pos->mouse_y1;
	pos->y2 = pos->y2 - y_zoom * pos->mouse_y2;
	if (HEIGHT <= WIDTH)
		pos->zoom = HEIGHT / (pos->x2 - pos->x1);
	else
		pos->zoom = WIDTH / (pos->y2 - pos->y1);
}

void	zoom_out(t_pos *pos)
{
	double	x_zoom;
	double	y_zoom;

	if (pos->iter_multiplier > 1)
		pos->iter_multiplier--;
	if (pos->iter_multiplier % 100 == 0)
		pos->iter_count -= 200;
	printf("iter_multiplier = %d \n", pos->iter_multiplier);
	printf("iter_count = %d \n", pos->iter_count);
	x_zoom = pos->delta_x - pos->delta_x * 0.95;
	y_zoom = pos->delta_y - pos->delta_y * 0.95;
	pos->x1 = pos->x1 - x_zoom * pos->mouse_x2;
	pos->x2 = pos->x2 + x_zoom * pos->mouse_x1;
	pos->y1 = pos->y1 - y_zoom * pos->mouse_y2;
	pos->y2 = pos->y2 + y_zoom * pos->mouse_y1;
	if (HEIGHT <= WIDTH)
		pos->zoom = HEIGHT / (pos->delta_x);
	else
		pos->zoom = WIDTH / (pos->delta_y);
}

void	zoom_from_mouse_position(int x, int y, t_pos *pos)
{
	pos->delta_x = pos->x2 - pos->x1;
	pos->delta_y = pos->y2 - pos->y1;
	pos->mouse_x1 = (double)x / WIDTH;
	pos->mouse_x2 = fabs(((double)x - WIDTH) / WIDTH);
	pos->mouse_y1 = (double)y / HEIGHT;
	pos->mouse_y2 = fabs(((double)y - HEIGHT) / HEIGHT);
}

int	mouse_pos(int button, int x, int y, void *param)
{
	if (button == 5)
	{
		zoom_from_mouse_position(x, y, ((t_all *)param)->p);
		zoom_in(((t_all *)param)->p);
		window_adapt(((t_all *)param)->p);
		mlx_destroy_image(((t_all *)param)->v->mlx,
			((t_all *)param)->v->img.mlx_img);
		if (((t_all *)param)->p->set == 1)
			create_mandelbrot(((t_all *)param)->p, ((t_all *)param)->v);
		else if (((t_all *)param)->p->set == 2)
			create_julia(((t_all *)param)->p, ((t_all *)param)->v);
	}
	if (button == 4)
	{
		zoom_from_mouse_position(x, y, ((t_all *)param)->p);
		zoom_out(((t_all *)param)->p);
		window_adapt(((t_all *)param)->p);
		mlx_destroy_image(((t_all *)param)->v->mlx,
			((t_all *)param)->v->img.mlx_img);
		if (((t_all *)param)->p->set == 1)
			create_mandelbrot(((t_all *)param)->p, ((t_all *)param)->v);
		else if (((t_all *)param)->p->set == 2)
			create_julia(((t_all *)param)->p, ((t_all *)param)->v);
	}
	return (1);
}
