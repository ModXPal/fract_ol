/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_julia_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcollas <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 11:48:33 by rcollas           #+#    #+#             */
/*   Updated: 2021/08/24 11:49:24 by rcollas          ###   ########.fr       */
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
	int		unit;
	int		sign;

	unit = 10;
	fnb = 0;
	sign = 1;
	if (*nb == '-')
	{
		sign = -1;
		nb++;
	}
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
	return (fnb * sign);
}
