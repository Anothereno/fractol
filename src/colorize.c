/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colorize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 17:06:04 by hdwarven          #+#    #+#             */
/*   Updated: 2019/04/11 17:51:24 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		color_func(int x, double p)
{
	return ((int)(255 * SQR(cos(sqrt(x) + p))));
}

void	set_pixel(t_union *my_union, int y, int x, double n)
{
	int point;

	point = x * 4 + my_union->sl * y;
	if (n == my_union->max_iter)
	{
		my_union->image_data[point] = 0;
		my_union->image_data[point + 1] = 0;
		my_union->image_data[point + 2] = 0;
	}
	else
	{
		my_union->image_data[point] =
				color_func(my_union->max_iter,
						my_union->scale * 0.0025);
		my_union->image_data[point + 1] =
				color_func(my_union->max_iter,
						n + my_union->scale * 0.0025);
		my_union->image_data[point + 2] =
				color_func(my_union->max_iter,
						0.5 * n + my_union->scale * 0.0025);
	}
}

void	write2map(char color, char *color_string, int i)
{
	char	bit;

	bit = (color >> 4) & 0x0f;
	if (bit <= 9)
		bit += '0';
	else
		bit += 'a' - 10;
	color_string[i] = bit;
	bit = color & 0x0f;
	if (bit <= 9)
		bit += '0';
	else
		bit += 'a' - 10;
	color_string[i + 1] = bit;
}

void	pixel_fdf(t_union *my_union, int n)
{
	int		color_red;
	int		color_green;
	int		color_blue;
	char	color_string[9];

	color_string[0] = '0';
	color_string[1] = 'x';
	color_string[8] = '\0';
	color_blue = color_func(my_union->max_iter, my_union->scale * 0.0025);
	color_green = color_func(my_union->max_iter, n + my_union->scale * 0.0025);
	color_red = color_func(my_union->max_iter, 0.5 *
		n + my_union->scale * 0.0025);
	write2map(color_red, color_string, 2);
	write2map(color_green, color_string, 4);
	write2map(color_blue, color_string, 6);
	fprintf(my_union->file, "%d,%s ", n, color_string);
}
