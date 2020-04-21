/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 22:56:07 by user              #+#    #+#             */
/*   Updated: 2020/04/21 22:56:07 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "fractols_list.h"
#include "color_schemes.h"

t_data	init_data(void)
{
	t_data	data;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		ft_error("can\'t initialize sdl", "init_data", 0);
	data.wnd.window = SDL_CreateWindow("fract-ol", SDL_WINDOWPOS_CENTERED,
													SDL_WINDOWPOS_CENTERED,
													WIDTH, HEIGHT, 0);
	if (data.wnd.window == NULL)
		ft_error("can\'t create window", "init_data", 0);
	data.wnd.wnd_surface = SDL_GetWindowSurface(data.wnd.window);
	data.cldata = opencl_init();
	data.fractol_type = MANDELBROT;
	data.julia_re = -0.488;
	data.julia_im = 0.596;
	data.pixels = WIDTH * HEIGHT;
	data.color_scheme = BGR;
	data.mouse.is_left_button_active = FALSE;
	data.mouse.is_right_button_active = FALSE;
	reset_fractol(&data);
	return (data);
}
