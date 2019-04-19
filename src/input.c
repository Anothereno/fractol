/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 19:07:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/04/17 17:20:15 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	struct_initial(t_union *my_union)
{

        my_union->win_x = 1000;
        my_union->win_y = 1000;
        my_union->scale = 1;
        my_union->shift_y = 0;
        my_union->kof = 1.2;
        my_union->zoom_num = 50;
        my_union->half_win_x = my_union->win_x * 0.5;
        my_union->half_win_y = my_union->win_y * 0.5;
        my_union->max_iter = 200;
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
