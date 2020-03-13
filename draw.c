#include <stdio.h>

#include "fractol.h"
#include "mlx_defines.h"
#include "mlx.h"
#include "fractols_list.h"

static void		setup_args(t_data *data)
{
	cl_int		ret;

	ret = 0;
	ret |= clSetKernelArg(data->cldata->kernel, 0, sizeof(cl_mem), &data->cldata->buf);
	ret |= clSetKernelArg(data->cldata->kernel, 1, sizeof(double), &data->camera.x);
	ret |= clSetKernelArg(data->cldata->kernel, 2, sizeof(double), &data->camera.y);
	ret |= clSetKernelArg(data->cldata->kernel, 3, sizeof(double), &data->camera.zoom);
	ret |= clSetKernelArg(data->cldata->kernel, 4, sizeof(int), &data->iters);
	ret |= clSetKernelArg(data->cldata->kernel, 5, sizeof(int), &data->fractol_type);
	ret |= clSetKernelArg(data->cldata->kernel, 6, sizeof(double), &data->julia_re);
	ret |= clSetKernelArg(data->cldata->kernel, 7, sizeof(double), &data->julia_im);
	ret |= clSetKernelArg(data->cldata->kernel, 8, sizeof(int), &data->color_scheme);
	if (ret != CL_SUCCESS)
		ft_assert(0, "Can\'t set args");
}

static void		execute(t_data *data)
{
	char		*info;
	cl_int		ret;
	size_t		info_len;

	ret = clEnqueueNDRangeKernel(data->cldata->command_queue,
								data->cldata->kernel, 1, NULL, &data->pixels,
								&data->cldata->work_size, 0, NULL, NULL);
	if (ret)
	{
		info = malloc(10000);
		clGetProgramBuildInfo(data->cldata->program, data->cldata->device_id,
								CL_PROGRAM_BUILD_LOG, 10000, info, &info_len);
		write(1, info, info_len);
		free(info);
		ft_error("can\'t execute kernel", "draw/execute", 0);
	}
}

static void		read_buffer(t_data *data)
{
	cl_int		ret;

	ret = clEnqueueReadBuffer(data->cldata->command_queue, data->cldata->buf,
				CL_TRUE, 0, data->pixels * 4, data->wnd.img, 0, NULL, NULL);
	if (ret)
		ft_error("can\'t read data from buffer to mlx surface",
				"draw/read_buffer", 0);
}

void			draw(t_data *data)
{
	setup_args(data);
	execute(data);
	read_buffer(data);
	mlx_put_image_to_window(data->wnd.mlxptr, data->wnd.wndptr, data->wnd.imgptr, 0, 0);
	char str[20];
	ft_memitoa(data->iters, str, 10, 0);
	mlx_string_put(data->wnd.mlxptr, data->wnd.wndptr, 10, 50, 0xFF0000, str);
	if (data->fractol_type == MANDELBROT)
		ft_memcpy(str, "MANDELBROT", 11);
	else if (data->fractol_type == MANDELBAR)
		ft_memcpy(str, "MANDELBAR", 10);
	else if (data->fractol_type == JULIA)
		ft_memcpy(str, "JULIA", 6);
	else if (data->fractol_type == NEWTON)
		ft_memcpy(str, "NEWTON", 7);
	mlx_string_put(data->wnd.mlxptr, data->wnd.wndptr, 10, 100, 0xFF0000, str);
}
