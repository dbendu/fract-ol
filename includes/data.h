/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:31:21 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/21 21:16:53 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# define ZOOM			1.2

# include "opencl.h"

typedef struct			s_wnd
{
	SDL_Window			*window;
	SDL_Surface			*wnd_surface;
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
