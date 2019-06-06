/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:42:02 by hdwarven          #+#    #+#             */
/*   Updated: 2019/05/07 13:46:01 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*draw_image(void *my_thread)
{
	int			x;
	int			y;
	t_thread	*thr;
	t_union		*my_union;

	thr = (t_thread *)my_thread;
	my_union = thr->my_union;
	y = thr->y_begin - 1;
	while (++y < thr->y_finish)
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
	}
	return (NULL);
}

void	plot(t_union *my_union)
{
	pthread_t	thread[NUM_OF_THR];
	t_thread	my_thread[NUM_OF_THR];
	int			i;

	i = -1;
	my_union->var_x = 0.2 * my_union->scale * my_union->win_x;
	my_union->var_y = 0.2 * my_union->scale * my_union->win_y;
	while (++i < NUM_OF_THR)
	{
		my_thread[i].id = i;
		my_thread[i].y_begin = i * (my_union->win_y / NUM_OF_THR);
		my_thread[i].my_union = my_union;
		my_thread[i].y_finish = i * (my_union->win_y / NUM_OF_THR)
				+ my_union->win_y / NUM_OF_THR;
		if (pthread_create(&thread[i], NULL, draw_image, &my_thread[i]))
			ft_putstr("Error in threads allocation\n");
	}
	i = NUM_OF_THR;
	while (--i >= 0)
		pthread_join(thread[i], NULL);
	if (my_union->cross)
		put_cross(my_union);
	mlx_put_image_to_window(my_union->mlx_ptr,
				my_union->win_ptr, my_union->image_ptr, 0, 0);
}

void	ship(t_union *my_union, int x, int y)
{
	t_var	var;
	int		n;

	var.new_real = (x - my_union->half_win_x) *
		(1 / my_union->var_x) + my_union->shift_x;
	var.new_imag = (y - my_union->half_win_y) *
			(1 / my_union->var_y) + my_union->shift_y;
	var.temp_x = var.new_real;
	var.temp_y = var.new_imag;
	n = -1;
	while (++n < my_union->max_iter && (SQR(var.new_real) +
		SQR(var.new_imag) < 4))
	{
		var.temp_real = SQR(var.new_real) - SQR(var.new_imag) + var.temp_x;
		var.new_imag = fabs(2 * var.new_real * var.new_imag) + var.temp_y;
		var.new_real = fabs(var.temp_real);
	}
	if (my_union->save_fdf)
		pixel_fdf(my_union, n);
	else
		set_pixel(my_union, y, x, n);
}

void	julia(t_union *my_union, int x, int y)
{
	t_var	var;
	int		n;

	var.new_real = (x - my_union->half_win_x) *
			(1 / my_union->var_x) + my_union->shift_x;
	var.new_imag = (y - my_union->half_win_y) *
			(1 / my_union->var_y) + my_union->shift_y;
	n = -1;
	while (++n < my_union->max_iter)
	{
		var.temp_real = var.new_real;
		var.temp_imag = var.new_imag;
		var.new_real = var.temp_real * var.temp_real -
				var.temp_imag * var.temp_imag + my_union->cur_real;
		var.new_imag = 2 * var.temp_real * var.temp_imag +
				my_union->cur_imag;
		if (var.temp_real * var.temp_real + var.temp_imag *
			var.temp_imag > 4)
			break ;
	}
	if (my_union->save_fdf)
		pixel_fdf(my_union, n);
	else
		set_pixel(my_union, y, x, n);
}

void	mandelbrot(t_union *my_union, int x, int y)
{
	t_var	var;
	int		n;

	var.temp_x = (x - my_union->half_win_x) *
		(1 / my_union->var_x) + my_union->shift_x;
	var.temp_y = (y - my_union->half_win_y) *
		(1 / my_union->var_y) + my_union->shift_y;
	var.new_real = 0;
	var.new_imag = 0;
	n = -1;
	while (++n < my_union->max_iter)
	{
		var.temp_real = var.new_real;
		var.temp_imag = var.new_imag;
		var.new_real = SQR(var.temp_real) - SQR(var.temp_imag)
			+ var.temp_x;
		var.new_imag = 2 * var.temp_real * var.temp_imag +
			var.temp_y;
		if (SQR(var.new_real) + SQR(var.new_imag) > 4)
			break ;
	}
	if (my_union->save_fdf)
		pixel_fdf(my_union, n);
	else
		set_pixel(my_union, y, x, n);
}
