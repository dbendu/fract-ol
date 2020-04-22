/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 21:05:30 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/22 12:20:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "fractols_list.h"

void			mouse_press(t_data *data, const SDL_MouseButtonEvent *event)
{
	if (event->button == SDL_BUTTON_LEFT)
	{
		data->mouse.is_left_button_active = TRUE;
		data->mouse.x = event->x;
		data->mouse.y = event->y;
	}
	else if (event->button == SDL_BUTTON_RIGHT)
		data->mouse.is_right_button_active = TRUE;
	if (event->button != SDL_BUTTON_LEFT && event->button != SDL_BUTTON_RIGHT)
		draw(data);
}

void			mouse_release(t_data *data, int button)
{
	if (button == SDL_BUTTON_LEFT)
		data->mouse.is_left_button_active = FALSE;
	else if (button == SDL_BUTTON_RIGHT)
		data->mouse.is_right_button_active = FALSE;
}

void			mouse_move(t_data *data, int x, int y)
{
	if (data->mouse.is_left_button_active)
	{
		data->camera.x += (data->mouse.x - x) / data->camera.zoom;
		data->camera.y += (y - data->mouse.y) / data->camera.zoom;
		data->mouse.x = x;
		data->mouse.y = y;
	}
	else if (data->fractol_type == JULIA && data->mouse.is_right_button_active)
	{
		data->julia_re = 4 * ((double)x / WIDTH - 0.5);
		data->julia_im = 4 * ((double)(HEIGHT - y) / HEIGHT - 0.5);
	}
	if (data->mouse.is_left_button_active ||
		(data->mouse.is_right_button_active && data->fractol_type == JULIA))
		draw(data);
	SDL_FlushEvent(SDL_MOUSEMOTION);
}

static void		zoom(int x, int y, t_data *data, int direction)
{
	const double	temp_x = (x - WIDTH / 2) / data->camera.zoom;
	const double	temp_y = (y - HEIGHT / 2) / data->camera.zoom;

	if (direction == 1)
	{
		data->camera.x = temp_x / ZOOM - temp_x + data->camera.x;
		data->camera.y = temp_y - temp_y / ZOOM + data->camera.y;
	}
	else
	{
		data->camera.x = temp_x * ZOOM - temp_x + data->camera.x;
		data->camera.y = temp_y - temp_y * ZOOM + data->camera.y;
	}
}

void			mouse_wheel(t_data *data, int direction)
{
	int		x;
	int		y;

	SDL_GetMouseState(&x, &y);
	if (direction < 0)
	{
		data->camera.zoom /= 1.2;
		zoom(x, y, data, 1);
	}
	else
	{
		data->camera.zoom *= 1.2;
		zoom(x, y, data, -1);
	}
	draw(data);
}
