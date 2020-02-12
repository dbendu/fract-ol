#include <stdio.h>
#include <stdlib.h>

#include "fractol.h"
#include "mlx_defines.h"

int				key_press(int button, t_data *data)
{
	// printf("%d\n", button);
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
	else if (button == NUM_MINUS && data->iters > 0)
		--data->iters;
	else if (button == NUM_PLUS)
		++data->iters;
	else if (button == SPACE)
	{
		data->iters = 50;
		data->camera.x = 0;
		data->camera.y = 0;
		data->camera.zoom = 140;
		data->mouse.x = WIDTH / 2;
		data->mouse.y = HEIGHT / 2;
	}
	draw(data);
	return (0);
}