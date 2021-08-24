/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:50:00 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/24 11:50:24 by rcollas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fract_ol.h"

int	is_number(char *str)
{
	int	dot;

	dot = 0;
	if (*str == '-')
		str++;
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
	if (ac != 4)
		return (0);
	if (ft_atof(av[1]) != 2)
		return (0);
	if (!is_number(av[2]))
		return (0);
	if (!is_number(av[3]))
		return (0);
	return (1);
}
