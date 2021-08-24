/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:02:22 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/24 11:52:03 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_putstr("missing arguments \n");
		return (0);
	}
	if (is_valid_mandelbrot(argc, argv))
	{
		ft_putstr("Creating mandelbrot set... \n");
		mandelbrot_set();
	}
	else if (is_valid_julia(argc, argv))
	{
		ft_putstr("Creating julia set... \n");
		julia_set(ft_atof(argv[2]), ft_atof(argv[3]));
	}
	else
	{
		ft_putstr("Please choose between the following options : \n");
		ft_putstr("Enter <1> for mandelbrot set \n");
		ft_putstr("Enter <2> for julia set \n");
		ft_putstr("For julia set please use the following format : \n");
		ft_putstr("<2> <nb1> <nb2> \n");
		ft_putstr("nb1/nb2 must be floating numbers between -4 and 4\n");
	}
	return (0);
}
