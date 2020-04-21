/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 21:03:35 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/21 22:47:15 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fractol.h"
#include "fractols_list.h"
#include "color_schemes.h"

static void		change_fractol(t_data *data, SDL_Keycode button)
{
	if (button == SDLK_PERIOD)
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
	reset_fractol(data);
}

static void		change_color_scheme(t_data *data)
{
	if (data->color_scheme == LAST_COLOR_SCHEME)
		data->color_scheme = FIRST_COLOR_SCHEME;
	else
		data->color_scheme += 1;
}

void			key_press(t_data *data, SDL_Keycode button)
{
	if (button == SDLK_UP)
		data->camera.y -= 10 / data->camera.zoom;
	else if (button == SDLK_DOWN)
		data->camera.y += 10 / data->camera.zoom;
	else if (button == SDLK_RIGHT)
		data->camera.x -= 10 / data->camera.zoom;
	else if (button == SDLK_LEFT)
		data->camera.x += 10 / data->camera.zoom;
	else if (button == SDLK_EQUALS)
		data->iters += 1;
	else if (button == SDLK_MINUS && data->iters > 0)
		data->iters -= 1;
	else if (button == SDLK_SPACE)
		reset_fractol(data);
	else if (button == SDLK_COMMA || button == SDLK_PERIOD)
		change_fractol(data, button);
	else if (button == SDLK_i)
		change_color_scheme(data);
	else if (button == SDLK_s)
		data->camera.zoom /= 1.2;
	else if (button == SDLK_w)
		data->camera.zoom *= 1.2;
	draw(data);
	SDL_FlushEvent(SDL_KEYDOWN);
}
