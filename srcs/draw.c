/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:26:53 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/21 23:10:40 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "fractols_list.h"

static void		setup_args(t_data *data, cl_kernel kernel)
{
	cl_int		ret;

	ret = 0;
	ret |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &data->cldata->buf);
	ret |= clSetKernelArg(kernel, 1, sizeof(double), &data->camera.x);
	ret |= clSetKernelArg(kernel, 2, sizeof(double), &data->camera.y);
	ret |= clSetKernelArg(kernel, 3, sizeof(double), &data->camera.zoom);
	ret |= clSetKernelArg(kernel, 4, sizeof(int), &data->iters);
	ret |= clSetKernelArg(kernel, 5, sizeof(int), &data->fractol_type);
	ret |= clSetKernelArg(kernel, 6, sizeof(double), &data->julia_re);
	ret |= clSetKernelArg(kernel, 7, sizeof(double), &data->julia_im);
	ret |= clSetKernelArg(kernel, 8, sizeof(int), &data->color_scheme);
	ft_assert(ret == CL_SUCCESS, "Can\'t set args");
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
				CL_TRUE, 0, data->pixels * 4,
				data->wnd.wnd_surface->pixels, 0, NULL, NULL);
	if (ret)
		ft_error("can\'t read data from buffer to mlx surface",
				"draw/read_buffer", 0);
}

void			draw(t_data *data)
{
	setup_args(data, data->cldata->kernel);
	execute(data);
	read_buffer(data);
	SDL_UpdateWindowSurface(data->wnd.window);
}
