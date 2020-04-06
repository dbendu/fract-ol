/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:26:19 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/06 12:41:54 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "mlx.h"
#include "mlx_defines.h"
#include "fractols_list.h"
#include "color_schemes.h"

void			fractol_exit(t_data *data)
{
	mlx_destroy_image(data->wnd.mlxptr, data->wnd.imgptr);
	mlx_destroy_window(data->wnd.mlxptr, data->wnd.wndptr);
	clReleaseContext(data->cldata->context);
	clReleaseCommandQueue(data->cldata->command_queue);
	clReleaseProgram(data->cldata->program);
	clReleaseKernel(data->cldata->kernel);
	clReleaseMemObject(data->cldata->buf);
	exit(0);
}

void			reset(t_data *data)
{
	data->iters = 50;
	data->camera.x = 0;
	data->camera.y = 0;
	data->camera.zoom = 140;
	data->mouse.x = WIDTH / 2;
	data->mouse.y = HEIGHT / 2;
}

t_data			data_create(void)
{
	t_data data;

	data.wnd.mlxptr = mlx_init();
	data.wnd.wndptr = mlx_new_window(data.wnd.mlxptr, WIDTH, HEIGHT,
									"fract'ol");
	data.wnd.imgptr = mlx_new_image(data.wnd.mlxptr, WIDTH, HEIGHT);
	data.wnd.img = (int*)mlx_get_data_addr(data.wnd.imgptr, &data.wnd.bytes,
									&data.wnd.size_line, &data.wnd.endian);
	data.cldata = opencl_init();
	data.fractol_type = MANDELBROT;
	data.julia_re = -0.488;
	data.julia_im = 0.596;
	data.pixels = WIDTH * HEIGHT;
	data.color_scheme = BGR;
	reset(&data);
	return (data);
}

int				main(void)
{
	t_data		data;

	data = data_create();
	draw(&data);
	mlx_hook(data.wnd.wndptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.wnd.wndptr, 4, 1L << 2, mouse_press, &data);
	mlx_hook(data.wnd.wndptr, 5, 1L << 3, mouse_release, &data);
	mlx_hook(data.wnd.wndptr, 6, 1L << 13, mouse_move, &data);
	mlx_loop(data.wnd.mlxptr);
	return (0);
}