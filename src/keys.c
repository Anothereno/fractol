/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:55:21 by hdwarven          #+#    #+#             */
/*   Updated: 2019/04/17 14:51:28 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double map_func(double z, double c_min, double c_max, double m_min, double m_max)
{
	return (z * 4 / c_max + m_min);
}

int	exit_(t_union *my_union)
{
//	mlx_destroy_window(my_union->mlx_ptr, my_union->win_ptr);
//	free(my_union->ints);
//	free(my_union->color);
//	clear_points(my_union);
//	free(my_union);
	exit(0);
    return (0);
}

void	max_plus(int key, t_union *my_union)
{
    if (key == 126)
	    my_union->max_iter += 5;
    if (key == 125)
        my_union->max_iter -= 5;
	plot(my_union);
}

int		mouse_move(int x, int y, t_union *my_union)
{
	if (my_union->mode == 'f')
	{
        my_union->cur_real = map_func(x, 0, my_union->win_x, -2, 2);
        my_union->cur_imag = map_func(y, 0, my_union->win_y, -2, 2);
		plot(my_union);
	}
}

int		mouse_press(int key, int x, int y, t_union *my_union)
{
//	ft_putnbr(key);
	if (key == 1 && (my_union->mode == 'j' || my_union->mode == 'f'))
		change_mode(my_union);
	if (key == 5 || key == 4)
		zoom(key, my_union, x, y);
}

int		deal_key(int key, void *param)
{
//    ft_putnbr(key);
 	if (key == 53)
		exit_((t_union*)param);
	if (key == 13 || key == 1)
		shift_y(key, (t_union*)param);
	if (key == 0 || key == 2)
		shift_x(key, (t_union*)param);
	if (key == 126 || key == 125)
		max_plus(key, (t_union*)param);
	return (0);
}
