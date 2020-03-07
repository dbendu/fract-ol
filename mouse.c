#include <stdio.h>

#include "fractol.h"
#include "mlx_defines.h"

static void		zoom(int x, int y, t_data *data, int direction)
{
	double		temp_x;
	double		temp_y;

	temp_x = (x - WIDTH / 2) / data->camera.zoom;
	temp_y = (y - HEIGHT / 2) / data->camera.zoom;
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

int				mouse_press(int button, int x, int y, t_data *data)
{
	if (x < 0 || y < 0 || x >= WIDTH || x >= HEIGHT)
		return (0);
	if (button == WHEEL_UP)
	{
		data->camera.zoom /= 1.2;
		zoom(x, y, data, 1);
	}
	else if (button == WHEEL_DOWN)
	{
		data->camera.zoom *= 1.2;
		zoom(x, y, data, -1);
	}
	else if (button == LEFT_BUTTON)
	{
		data->mouse.is_left_button_active = TRUE;
		data->mouse.x = x;
		data->mouse.y = y;
	}
	if (button != LEFT_BUTTON)
		draw(data);
	return (1);
}

int				mouse_release(int button, int x, int y, t_data *data)
{
	if (button == LEFT_BUTTON)
		data->mouse.is_left_button_active = FALSE;
	(void)x;
	(void)y;
	return (1);
}


int				mouse_move(int x, int y, t_data *data)
{
	if (data->mouse.is_left_button_active)
	{
		data->camera.x += (data->mouse.x - x) / data->camera.zoom;
		data->camera.y += (y - data->mouse.y) / data->camera.zoom;
		data->mouse.x = x;
		data->mouse.y = y;
	}
	draw(data);
	return (1);
}
