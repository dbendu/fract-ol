/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:31:21 by dbendu            #+#    #+#             */
/*   Updated: 2020/03/16 22:16:04 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define ZOOM			1.2

# include "opencl.h"

typedef struct			s_wnd
{
	void				*mlxptr;
	void				*wndptr;
	void				*imgptr;
	int					*img;
	int					bytes;
	int					size_line;
	int					endian;
}						t_wnd;

typedef struct			s_camera
{
	double				x;
	double				y;
	double				zoom;
}						t_camera;

typedef struct			s_mouse
{
	int					x;
	int					y;
	t_bool				is_left_button_active;
	t_bool				is_right_button_active;
}						t_mouse;

typedef struct			s_data
{
	t_wnd				wnd;
	t_camera			camera;
	t_mouse				mouse;
	t_cldata			*cldata;
	int					iters;
	int					fractol_type;
	double				julia_re;
	double				julia_im;
	size_t				pixels;
	int					color_scheme;
}						t_data;

#endif
