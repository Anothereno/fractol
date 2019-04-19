/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdwarven <hdwarven@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:51:07 by hdwarven          #+#    #+#             */
/*   Updated: 2019/04/17 17:43:26 by hdwarven         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef FDF_FDF_H
# define FDF_FDF_H
# define ABS(x) (x < 0) ? x = -x : x
# define MIN(a, b) (a < b) ? a : b
# define TR (my_union)->transform
# define SQR(x) x * x
# define ABS(x) x >= 0 ? x : (x * -1)
# define UPTR (*my_union)
# include "/usr/local/include/mlx.h"
# include <math.h>
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
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
	int			max_z;
	int			min_z;
	double		divisor;
	int			max_color;
	int			min_color;
	int 		max_iter;
	double		cur_real;
	double		cur_imag;
    double		pr_real;
    double		pr_imag;
    double      multi_shift_x;
    double      multi_shift_y;
	int         zoom_num;
    double		kof;
    double		old;
	int			ave;
	double      half_win_x;
    double      half_win_y;
    double      var_x;
    double      var_y;
	char 		mode;
    double		shift_y;
	int			win_y;
	int			bpp;
	int			endian;
	int			sl;
}				t_union;

typedef struct	s_thread
{
	int id;
	int y_begin;
	int y_finish;
	t_union *my_union;
}				t_thread;

void            octo(t_union *my_union, int x, int y);
void            ship(t_union *my_union, int x, int y);
void            put_cross(t_union *my_union);
void            newton(t_union *my_union, int x, int y);
void        	mandelbrot(t_union *my_union, int x, int y);
int		        mouse_move(int x, int y, t_union *param);
int		        mouse_press(int key, int x, int y, t_union *param);
int             color(t_union **my_union, int n, int max);
void			print_error(const char *msg, t_union *my_union);
void			image_put(t_union **my_union);
void			julia(t_union *my_union, int x, int y);
void			set_pixel(t_union *my_union, int y, int x, double n);
void			image_init(t_union *my_union);
int				calc_scale(t_union **my_union);
void			change_mode(t_union *my_union);
void			shift_coordinates(t_union **my_union, int i, int j);
void			shift_x(int key, t_union *my_union);
void			shift_y(int key, t_union *my_union);
void			zoom(int key, t_union *my_union, int x, int y);
int		    	exit_(t_union *my_union);
void			plot(t_union *my_union);
int				grid_valid(t_union ***my_union, int *x, int *y);
int				deal_key(int key, void *param);
int				take_sign(int x);
char			*take_coordinates(char *argv);
char			*reading(int fd);
void			struct_initial(t_union *my_union);

#endif
