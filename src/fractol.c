/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 17:23:42 by hdwarven          #+#    #+#             */
/*   Updated: 2019/06/06 19:14:31 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		set_mode(t_union *my_union, char *argv)
{
	if (ft_strequ(argv, "julia"))
	{
		my_union->mode = 'j';
		return (1);
	}
	else if (ft_strequ(argv, "mandelbrot"))
	{
		my_union->mode = 'm';
		return (1);
	}
	else if (ft_strequ(argv, "ship"))
	{
		my_union->mode = 's';
		return (1);
	}
	return (0);
}

void	usage(void)
{
	ft_putstr("usage: ./fractol <argument>\n");
	ft_putstr("\targuments:\n");
	ft_putstr("\t\tjulia\t\tPrint Julia's fractal\n");
	ft_putstr("\t\tmandelbrot\tPrint Mandelbrot's fractal\n");
	ft_putstr("\t\tship\t\tPrint Burning ship fractal\n");
}

int		main(int argc, char **argv)
{
	t_union		my_union;

	if (argc == 2)
	{
		if (!set_mode(&my_union, argv[1]))
		{
			usage();
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
		usage();
	return (0);
}
