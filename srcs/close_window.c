/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:57:04 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/24 11:57:37 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

int	close_window(int keycode, t_vars *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(vars->mlx, vars->img.mlx_img);
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	return (0);
}
