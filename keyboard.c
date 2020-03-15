/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbendu <dbendu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 21:03:35 by dbendu            #+#    #+#             */
/*   Updated: 2020/03/14 21:04:07 by dbendu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx_defines.h"
#include "fractols_list.h"
#include "color_schemes.h"

static void		change_fractol(t_data *data, int button)
{
	if (button == MORE)
	{
		if (data->fractol_type == LAST_FRACTOL)
			data->fractol_type = FIRST_FRACTOL;
		else
			++data->fractol_type;
	}
	else
	{
		if (data->fractol_type == FIRST_FRACTOL)
			data->fractol_type = LAST_FRACTOL;
		else
			--data->fractol_type;
	}
	reset(data);
}

static void		change_color_scheme(t_data *data)
{
	if (data->color_scheme == LAST_COLOR_SCHEME)
		data->color_scheme = FIRST_COLOR_SCHEME;
	else
		data->color_scheme += 1;
}

int				key_press(int button, t_data *data)
{
	if (button == ESC)
		exit(0);
	else if (button == RIGHT)
		data->camera.x -= 10 / data->camera.zoom;
	else if (button == LEFT)
		data->camera.x += 10 / data->camera.zoom;
	else if (button == UP)
		data->camera.y -= 10 / data->camera.zoom;
	else if (button == DOWN)
		data->camera.y += 10 / data->camera.zoom;
	else if (button == PLUS)
		data->camera.zoom *= 1.2;
	else if (button == MINUS)
		data->camera.zoom /= 1.2;
	else if (button == S && data->iters > 0)
		--data->iters;
	else if (button == W)
		++data->iters;
	else if (button == SPACE)
		reset(data);
	else if (button == MORE || button == LESS)
		change_fractol(data, button);
	else if (button == I)
		change_color_scheme(data);
	draw(data);
	return (0);
}
