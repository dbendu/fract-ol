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
	ret |= clSetKernelArg(data->cldata->kernel, 3, sizeof(float), &data->camera.zoom);
	ret |= clSetKernelArg(data->cldata->kernel, 4, sizeof(int), &data->iters);
	ret |= clSetKernelArg(data->cldata->kernel, 5, sizeof(int), &data->fractol_type);
	ret |= clSetKernelArg(data->cldata->kernel, 6, sizeof(double), &data->julia_re);
	ret |= clSetKernelArg(data->cldata->kernel, 7, sizeof(double), &data->julia_im);
	if (ret != CL_SUCCESS)
		ft_assert(0, "Can\'t set args");
}

void			draw(t_data *data)
{
	setup_args(data);
	size_t size = WIDTH * HEIGHT;
	size_t threads = data->cldata->threads;
	int ret = clEnqueueNDRangeKernel(data->cldata->command_queue, data->cldata->kernel, 1, NULL, &size, &threads, 0, NULL, NULL);
	if (ret)
	{
		char result[4096];
		size_t size;
		clGetProgramBuildInfo(data->cldata->program, data->cldata->device_id, CL_PROGRAM_BUILD_LOG, sizeof(result), result, &size);
		printf("%s\n", result);
	}
	ft_assert(ret == 0, "Can\'t ex kernel");
	clEnqueueReadBuffer(data->cldata->command_queue, data->cldata->buf, CL_TRUE, 0, WIDTH * HEIGHT * 4, data->wnd.img, 0, NULL, NULL);
	mlx_put_image_to_window(data->wnd.mlxptr, data->wnd.wndptr, data->wnd.imgptr, 0, 0);
	char str[20];
	ft_memitoa(data->iters, str, 10, 0);
	mlx_string_put(data->wnd.mlxptr, data->wnd.wndptr, 10, 50, 0xFF0000, str);
	if (data->fractol_type == MANDELBROT)
		ft_memcpy(str, "MANDELBROT", 11);
	else if (data->fractol_type == MANDELBAR)
		ft_memcpy(str, "MANDELBAR", 10);
	else if (data->fractol_type == JULIA)
		ft_memcpy(str, "JULIA", 10);
	mlx_string_put(data->wnd.mlxptr, data->wnd.wndptr, 10, 100, 0xFF0000, str);
}
