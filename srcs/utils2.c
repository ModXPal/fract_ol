/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 00:49:44 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/12 21:23:23 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

void	init_img(t_img *img)
{
	img->mlx_img = 0;
	img->addr = 0;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = 0;
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}
