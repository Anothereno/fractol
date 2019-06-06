/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/05/07 14:07:59 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	struct_initial(t_union *my_union)
{
	my_union->win_x = 600;
	my_union->win_y = 600;
	my_union->scale = 1;
	my_union->save_fdf = 0;
	my_union->shift_y = 0;
	my_union->zoom_num = 50;
	my_union->cross = 0;
	my_union->half_win_x = my_union->win_x * 0.5;
	my_union->half_win_y = my_union->win_y * 0.5;
	my_union->max_iter = 100;
	my_union->cur_real = -0.7;
	my_union->cur_imag = 0.27015;
	my_union->mlx_ptr = mlx_init();
	my_union->win_ptr = mlx_new_window(my_union->mlx_ptr,
			my_union->win_x, my_union->win_y, "fractol");
	image_init(my_union);
}

void	image_init(t_union *my_union)
{
	my_union->image_ptr = mlx_new_image(my_union->mlx_ptr,
			my_union->win_x, my_union->win_y);
	my_union->image_data = mlx_get_data_addr(my_union->image_ptr,
			&(my_union->bpp), &(my_union->sl), &(my_union->endian));
}

void	create_fdf(t_union *my_union)
{
	int x;
	int y;

	my_union->file = fopen("fractol.fdf", "wt");
	my_union->save_fdf = 1;
	y = -1;
	while (++y < my_union->win_y)
	{
		x = -1;
		while (++x < my_union->win_x)
		{
			if (my_union->mode == 's')
				ship(my_union, x, y);
			else if (my_union->mode == 'j' || my_union->mode == 'f')
				julia(my_union, x, y);
			else if (my_union->mode == 'm')
				mandelbrot(my_union, x, y);
		}
		fprintf(my_union->file, "\n");
	}
	fclose(my_union->file);
	my_union->save_fdf = 0;
}
