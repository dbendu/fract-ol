/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 21:04:20 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/06 12:10:29 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

#include "libft.h"
#include "opencl.h"
#include "mlx_defines.h"

#define MAX_SOURCE_SIZE	100000

static void				cl_exit(char *msg)
{
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

static void				opencl_create_infrastruct(t_cldata *cldata)
{
	cl_int			ret;

	ret = clGetPlatformIDs(1, &cldata->platform_id,
		&cldata->num_platforms);
	ft_assert(ret == CL_SUCCESS, "Can\'t get platforms");
	ret = clGetDeviceIDs(cldata->platform_id, CL_DEVICE_TYPE_GPU, 1,
		&cldata->device_id, &cldata->num_devices);
	ft_assert(ret == CL_SUCCESS, "Can\'t get devices");
	cldata->context = clCreateContext(NULL, 1, &cldata->device_id, NULL, NULL,
		&ret);
	ft_assert(ret == CL_SUCCESS, "Can\'t create context");
	cldata->command_queue = clCreateCommandQueue(cldata->context,
		cldata->device_id, 0, &ret);
	ft_assert(ret == CL_SUCCESS, "Can\'t create command queue");
}

static char				*opencl_read_kernel_from_file(void)
{
	char			*source_str;
	int				fd;
	ssize_t			read_ret;

	fd = open(KERNEL_FILE, O_RDONLY);
	ft_assert(fd > 0, "Can\'t open file");
	source_str = malloc(MAX_SOURCE_SIZE);
	read_ret = read(fd, source_str, MAX_SOURCE_SIZE);
	close(fd);
	source_str[read_ret] = '\0';
	return (source_str);
}

static void				opencl_compile_kernel(t_cldata *cldata, char *source)
{
	cl_int				ret;
	char				*info;
	size_t				info_len;

	cldata->program = clCreateProgramWithSource(cldata->context, 1,
		(const char**)&source, NULL, &ret);
	ft_assert(ret == CL_SUCCESS, "Can\'t create program from source");
	ret = clBuildProgram(cldata->program, 1, &cldata->device_id,
		"-I includes", NULL, NULL);
	if (ret)
	{
		info = malloc(MAX_SOURCE_SIZE);
		clGetProgramBuildInfo(cldata->program, cldata->device_id,
				CL_PROGRAM_BUILD_LOG, MAX_SOURCE_SIZE, info, &info_len);
		write(1, info, info_len);
		write(1, "\n", 1);
		free(info);
		cl_exit("Can\'t build program");
	}
	cldata->kernel = clCreateKernel(cldata->program, "eval", &ret);
	ft_assert(ret == CL_SUCCESS, "Can\'t create kernel");
}

t_cldata				*opencl_init(void)
{
	t_cldata		*cldata;
	char			*kernel_src;
	cl_int			ret;

	cldata = malloc(sizeof(t_cldata));
	ft_assert(cldata != NULL, "Can\'t allocate cldata");
	opencl_create_infrastruct(cldata);
	kernel_src = opencl_read_kernel_from_file();
	opencl_compile_kernel(cldata, kernel_src);
	free(kernel_src);
	cldata->buf = clCreateBuffer(cldata->context, CL_MEM_WRITE_ONLY,
								WIDTH * HEIGHT * sizeof(int), NULL,
								&ret);
	ft_assert(ret == CL_SUCCESS, "Can\'t create buffer");
	cldata->work_size = 200;
	return (cldata);
}
