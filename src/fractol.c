/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 16:31:34 by hdwarven          #+#    #+#             */
/*   Updated: 2019/04/17 13:53:55 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		main(int argc, char **argv)
{
	t_union		my_union;

	if (argc == 2)
	{
		if (ft_strequ(argv[1], "julia"))
			my_union.mode = 'j';
		else if (ft_strequ(argv[1], "mandelbrot"))
            my_union.mode = 'm';
        else if (ft_strequ(argv[1], "newton"))
            my_union.mode = 'n';
		else
		{
			ft_putstr("usage: ./fractol [mandelbrot/julia]\n");
			return (0);
		}
		struct_initial(&my_union);
		plot(&my_union);
		mlx_hook(my_union.win_ptr, 2, 5, deal_key, &my_union);
		mlx_hook(my_union.win_ptr, 17, 1L >> 17, exit_, &my_union);
        mlx_hook(my_union.win_ptr, 4, 5, mouse_press, &my_union);
        mlx_hook(my_union.win_ptr, 6, 5, mouse_move, &my_union);
		mlx_loop(my_union.mlx_ptr);
	}
	else
		ft_putstr("usage: ./fractol [mandelbrot/julia]\n");
	return (0);
}
