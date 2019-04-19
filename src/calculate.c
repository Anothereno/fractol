/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 17:42:02 by hdwarven          #+#    #+#             */
/*   Updated: 2019/04/17 18:51:12 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdlib.h>

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
            else if (my_union->mode == 'o')
		    {
			    my_union->old = 1;
			    octo(my_union, x, y);
		    }
			else if (my_union->mode == 'm')
				mandelbrot(my_union, x, y);
			else if (my_union->mode == 'n')
			{
				my_union->old = 1;
				newton(my_union, x, y);
			}
		}
	}
}

void	plot(t_union *my_union)
{
	pthread_t	thread[NUM_OF_THR];
	t_thread	my_thread[NUM_OF_THR];
	int			rc;
	int			i;

	i = -1;
	my_union->var_x = 0.2 * my_union->scale * my_union->win_x;
	my_union->var_y = 0.2 * my_union->scale * my_union->win_y;
	while (++i < NUM_OF_THR)
	{
		my_thread[i].id = i;
		my_thread[i].y_begin = i * (my_union->win_y / NUM_OF_THR);
		my_thread[i].my_union = my_union;
		my_thread[i].y_finish = i * (my_union->win_y / NUM_OF_THR) + my_union->win_y / NUM_OF_THR;
		rc = pthread_create(&thread[i], NULL, draw_image, &my_thread[i]);
		if (rc)
		{
			ft_putendl("Crash with code ");
			ft_putnbr(rc);
			ft_putchar('\n');
		}
	}
    i = -1;
    while (++i < NUM_OF_THR)
        pthread_join(thread[i], NULL);

	put_cross(my_union);
		mlx_put_image_to_window(my_union->mlx_ptr,
				my_union->win_ptr, my_union->image_ptr, 0, 0);
	mlx_string_put(my_union->mlx_ptr,
				   my_union->win_ptr, 20, 40, 0x000000, ft_itoa((int)my_union->scale));
	mlx_string_put(my_union->mlx_ptr,
				   my_union->win_ptr, 20, 20, 0x000000, ft_itoa(my_union->zoom_num));
}

//void	plot(t_union *my_union)
//{
//    int x;
//    int y;
//    pthread_t thread[4];
//    int rc;
//    int i;
//
//    my_union->var_x = 0.2 * my_union->scale * my_union->win_x;
//    my_union->var_y = 0.2 * my_union->scale * my_union->win_y;
//    y = -1;
//    while (++y < my_union->win_y)
//    {
//        x = -1;
//        while (++x < my_union->win_x)
//        {
//			if (my_union->mode == 'j' || my_union->mode == 'f')
//                julia(my_union, x, y);
//            if (my_union->mode == 'm')
//                mandelbrot(my_union, x, y);
//            if (my_union->mode == 'n')
//			{
//            	my_union->old = 1;
//				newton(my_union, x, y);
//			}
//        }
//    }
//	put_cross(my_union);
//    mlx_put_image_to_window(my_union->mlx_ptr,
//                            my_union->win_ptr, my_union->image_ptr, 0, 0);
//    mlx_string_put(my_union->mlx_ptr,
//            my_union->win_ptr, 20, 40, 0x000000, ft_itoa((int)my_union->scale));
//    mlx_string_put(my_union->mlx_ptr,
//            my_union->win_ptr, 20, 20, 0x000000, ft_itoa(my_union->zoom_num));
//}

void    put_cross(t_union *my_union)
{
    int i;

    i = 0;
    set_pixel(my_union, my_union->win_y / 2, my_union->win_x / 2, my_union->max_iter);
    while (++i < 10)
    {
        set_pixel(my_union, my_union->win_y / 2, my_union->win_x / 2 + i, my_union->max_iter);
        set_pixel(my_union, my_union->win_y / 2, my_union->win_x / 2 - i, my_union->max_iter);
        set_pixel(my_union, my_union->win_y / 2 + i, my_union->win_x / 2, my_union->max_iter);
        set_pixel(my_union, my_union->win_y / 2 - i, my_union->win_x / 2, my_union->max_iter);
    }
}

void    ship(t_union *my_union, int x, int y)
{
    double dub;
    double temp_real;
    double temp_imag;
    double new_real;
    double temp_x;
    double temp_y;
    double new_imag;
    int n;

    new_real = (x - my_union->half_win_x) * (1 / my_union->var_x) + my_union->shift_x;
    new_imag = (y - my_union->half_win_y) * (1 / my_union->var_y) + my_union->shift_y;
    temp_x = new_real;
    temp_y = new_imag;
    n = -1;
    while (++n < my_union->max_iter)
    {
        temp_real = SQR(new_real) - SQR(new_imag) + temp_x;
        new_imag = fabs(2 * new_real * new_imag) + temp_y;
        new_real = fabs(temp_real);
        if (SQR(new_real) + SQR(new_imag) > 4)
            break;
    }
//			dub = n + 1 - (log(2) / (sqrt(SQR(new_real) + SQR(new_imag)))) / log(2);
    set_pixel(my_union, y, x, n);
}

void    newton(t_union *my_union, int x, int y)
{
    double cur_real;
    double cur_imag;
    double new_real;
    double new_imag;
    double sqr_real;
    double sqr_imag;
    double dub;
    int n;

    cur_real = (x - my_union->half_win_x) / my_union->var_x + my_union->shift_x;
    cur_imag = (y - my_union->half_win_y) / my_union->var_y + my_union->shift_y;
    n = -1;
    while (++n < my_union->max_iter && my_union->old > 0.5)
    {
        new_real = cur_real;
        new_imag = cur_imag;
        sqr_real = SQR(cur_real);
        sqr_imag = SQR(cur_imag);
        my_union->old = (sqr_real + sqr_imag) * (sqr_real + sqr_imag);
        cur_real = (2 * new_real * my_union->old + sqr_real - sqr_imag) / (3 * my_union->old);
        cur_imag = 2 * cur_imag * (my_union->old - new_real) / (3 * my_union->old);
        my_union->old = (cur_real - new_real) * (cur_real - new_real) + (cur_imag - new_imag) * (cur_imag - new_imag);
    }
//            dub = n + 1 - (log(2) / (sqrt(SQR(new_real) + SQR(new_imag)))) / log(2);
    set_pixel(my_union, y, x, n);

}

void    octo(t_union *my_union, int x, int y)
{
    double cur_real;
    double cur_imag;
    double new_real;
    double new_imag;
    double sqr_real;
    double sqr_imag;
    double dub;
    int n;

    cur_real = (x - my_union->half_win_x) / my_union->var_x + my_union->shift_x;
    cur_imag = (y - my_union->half_win_y) / my_union->var_y + my_union->shift_y;
    n = -1;
    while (++n < my_union->max_iter && my_union->old > 0.5)
    {
        new_real = cur_real;
        new_imag = cur_imag;
        sqr_real = SQR(cur_real);
        sqr_imag = SQR(cur_imag);
		my_union->old = (sqr_real + sqr_imag) * (sqr_real + sqr_imag);
        cur_real = (2 * new_real * my_union->old + sqr_real - sqr_imag) / (3 * my_union->old);
        cur_imag = 2 * cur_imag * (my_union->old - new_real) / (3 * my_union->old);
		my_union->old = (cur_real - new_real) * (cur_real - new_real) + (cur_imag - new_imag) * (cur_imag - new_imag);
    }
//            dub = n + 1 - (log(2) / (sqrt(SQR(new_real) + SQR(new_imag)))) / log(2);
    set_pixel(my_union, y, x, n);

}

void	julia(t_union *my_union, int x, int y)
{

	double dub;
	double temp_real;
	double temp_imag;
	double new_real;
	double new_imag;
	int n;

    new_real = (x - my_union->half_win_x) * (1 / my_union->var_x) + my_union->shift_x;
    new_imag = (y - my_union->half_win_y) * (1 / my_union->var_y) + my_union->shift_y;
    n = -1;
    while (++n < my_union->max_iter)
    {
        temp_real = new_real;
        temp_imag = new_imag;
        new_real = temp_real * temp_real - temp_imag * temp_imag + my_union->cur_real;
        new_imag = 2 * temp_real * temp_imag + my_union->cur_imag;
        if (temp_real * temp_real + temp_imag * temp_imag > 4)
            break;
    }
//			dub = n + 1 - (log(2) / (sqrt(SQR(new_real) + SQR(new_imag)))) / log(2);
    set_pixel(my_union, y, x, n);
}

void	mandelbrot(t_union *my_union, int x, int y)
{
    double temp_real;
    double temp_imag;
    double pr_real;
    double pr_imag;
    double new_real;
    double new_imag;
    double dub;
    int n;

    pr_real = (x - my_union->half_win_x) * (1 / my_union->var_x) + my_union->shift_x;
    pr_imag = (y - my_union->half_win_y) * (1 / my_union->var_y) + my_union->shift_y;
    new_real = 0;
    new_imag = 0;
    n = -1;
    while (++n < my_union->max_iter)
    {
        temp_real = new_real;
        temp_imag = new_imag;
        new_real = SQR(temp_real) - SQR(temp_imag) + pr_real;
        new_imag = 2 * temp_real * temp_imag + pr_imag;
        if (SQR(new_real) + SQR(new_imag) > 4)
            break;
    }
//            dub = n + 1 - (log(2) / (sqrt(SQR(new_real) + SQR(new_imag)))) / log(2);
    set_pixel(my_union, y, x, n);
}