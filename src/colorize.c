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

int color_func(int x, double p)
{
	return ((int)(255 * SQR(cos(sqrt(x) + p))));
}

void	set_pixel(t_union *my_union, int y, int x, double n) {
	int point;

	point = x * 4 + my_union->sl * y;
	if (n == my_union->max_iter)
	{
        my_union->image_data[point] = 0;//(int)(sin(i * M_PI * 2 - M_PI_2) + 1) / 2 * 255;
        my_union->image_data[point + 1] = 0;//(int)(sin(i * M_PI * 4 - M_PI_2) + 1) / 2 * 255;
        my_union->image_data[point + 2] = 0;//(int)(sin(i * M_PI * 8 - M_PI_2) + 1) / 2 * 255;
	}
	else
    {
        my_union->image_data[point] = color_func(my_union->max_iter, my_union->scale * 0.0025);
        my_union->image_data[point + 1] = color_func(my_union->max_iter, n + my_union->scale * 0.0025);
        my_union->image_data[point + 2] = color_func(my_union->max_iter, 0.5 * n + my_union->scale * 0.0025);
	}
}
