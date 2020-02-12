#include <stdio.h>

#include "fractol.h"
#include "mlx_defines.h"
#include "mlx.h"
#include "complex.h"

static void		setup_args(t_data *data)
{
	cl_int		ret;

	ret = 0;
	// printf("%")
	ret |= clSetKernelArg(data->cldata->kernel, 0, sizeof(cl_mem), &data->cldata->buf);
	ret |= clSetKernelArg(data->cldata->kernel, 1, sizeof(int), &data->width);
	ret |= clSetKernelArg(data->cldata->kernel, 2, sizeof(int), &data->height);
	ret |= clSetKernelArg(data->cldata->kernel, 3, sizeof(int), &data->cldata->threads);
	ret |= clSetKernelArg(data->cldata->kernel, 4, sizeof(double), &data->camera.x);
	ret |= clSetKernelArg(data->cldata->kernel, 5, sizeof(double), &data->camera.y);
	ret |= clSetKernelArg(data->cldata->kernel, 6, sizeof(float), &data->camera.zoom);
	ret |= clSetKernelArg(data->cldata->kernel, 7, sizeof(int), &data->iters);
	if (ret != CL_SUCCESS)
		ft_assert(0, "Can\'t set args");
}

void			draw(t_data *data)
{
	setup_args(data);
	size_t size = data->width * data->height;
	size_t threads = data->cldata->threads;
	int ret = clEnqueueNDRangeKernel(data->cldata->command_queue, data->cldata->kernel, 1, NULL, &size, &threads, 0, NULL, NULL);
	// printf("%d\n", ret);
	ft_assert(ret == 0, "Can\'t ex kernel");
	clEnqueueReadBuffer(data->cldata->command_queue, data->cldata->buf, CL_TRUE, 0, data->width * data->height * 4, data->wnd.img, 0, NULL, NULL);
	mlx_put_image_to_window(data->wnd.mlxptr, data->wnd.wndptr, data->wnd.imgptr, 0, 0);
	char str[5];
	ft_itoa(data->iters, str, 10, 0);
	mlx_string_put(data->wnd.mlxptr, data->wnd.wndptr, 10, 50, 0xFFFFFF, str);
}


