/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:03:11 by hdwarven          #+#    #+#             */
/*   Updated: 2019/05/07 16:48:59 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __FRACTOL_H
# define __FRACTOL_H
# define SQR(x) x * x
# include "/usr/local/include/mlx.h"
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# define NUM_OF_THR 200

typedef struct	s_union
{
	void		*image_ptr;
	void		*mlx_ptr;
	char		*image_data;
	void		*win_ptr;
	double		scale;
	int			win_x;
	double		shift_x;
	int			max_iter;
	double		cur_real;
	double		cur_imag;
	int			zoom_num;
	double		temp_real;
	double		half_win_x;
	double		half_win_y;
	int			cross;
	double		var_x;
	double		var_y;
	char		mode;
	double		shift_y;
	int			win_y;
	int			bpp;
	int			save_fdf;
	int			endian;
	int			sl;
	FILE		*file;
}				t_union;

typedef struct	s_var
{
	double	temp_real;
	double	temp_imag;
	double	new_real;
	double	temp_x;
	double	temp_y;
	double	new_imag;
}				t_var;

typedef struct	s_thread
{
	int		id;
	int		y_begin;
	int		y_finish;
	t_union	*my_union;
}				t_thread;

void			create_fdf(t_union *my_union);
void			pixel_fdf(t_union *my_union, int n);
void			ship(t_union *my_union, int x, int y);
void			put_cross(t_union *my_union);
void			mandelbrot(t_union *my_union, int x, int y);
int				mouse_move(int x, int y, t_union *param);
int				mouse_press(int key, int x, int y, t_union *param);
void			julia(t_union *my_union, int x, int y);
void			set_pixel(t_union *my_union, int y, int x, double n);
void			image_init(t_union *my_union);
void			change_mode(t_union *my_union);
void			shift_x(int key, t_union *my_union);
void			shift_y(int key, t_union *my_union);
void			zoom(int key, t_union *my_union);
int				exit_(t_union *my_union);
void			plot(t_union *my_union);
int				deal_key(int key, t_union *param);
void			usage(void);
void			struct_initial(t_union *my_union);

#endif
