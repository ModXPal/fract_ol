/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 15:02:22 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/12 21:29:01 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

double	ft_atof(char *nb)
{
	double	fnb;
	int	unit;

	unit = 10;
	fnb = 0;
	while (is_digit(*nb))
	{
		if (*nb == '.')
			break ;
		fnb = fnb * 10 + *nb++ - 48;
	}
	if (*nb)
		nb++;
	while (is_digit(*nb))
	{
		fnb = fnb + (double)(*nb++ - 48) / unit;
		unit *= 10;
	}
	return (fnb);
}

int	is_number(char *str)
{
	int	dot;

	dot = 0;
	while (is_digit(*str))
	{
		if (*(str + 1) == 0)
			return (1);
		str++;
		if (*str == '.' && !dot)
		{
			dot = 1;
			str++;
		}
	}
	return (0);
}

int	is_valid_mandelbrot(int ac, char **av)
{
	if (ac != 2)
		return (0);
	if (ft_atof(av[1]) != 1)
		return (0);
	return (1);
}

int	is_valid_julia(int ac, char **av)
{
	float	MAX;
	float	MIN;

	MAX = 4000;
	MIN = -4000;
	if (ac != 4)
		return (0);
	if (ft_atof(av[1]) != 2)
		return (0);
	if (ft_atof(av[2]) > MAX)
		return (0);
	if (ft_atof(av[2]) < MIN)
		return (0);
	if (ft_atof(av[3]) > MAX)
		return (0);
	if (ft_atof(av[3]) < MIN)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	//printf("%f \n", ft_atof(argv[2]));
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
