#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "opencl.h"
#include "mlx_defines.h"
#include "libft.h"

#define MAX_SOURCE_SIZE	10000

static void				cl_exit(char *msg)
{
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

static void				opencl_create_infrastruct(t_cldata *cldata)
{
	cldata->ret = clGetPlatformIDs(1, &cldata->platform_id,
		&cldata->ret_num_platforms);
	if (cldata->ret)
		cl_exit("Can\'t get platforms");
	cldata->ret = clGetDeviceIDs(cldata->platform_id, CL_DEVICE_TYPE_GPU, 1,
		&cldata->device_id, &cldata->ret_num_devices);
	if (cldata->ret)
		cl_exit("Can\'t get devices");
	cldata->context = clCreateContext(NULL, 1, &cldata->device_id, NULL, NULL,
		&cldata->ret);
	if (cldata->ret)
		cl_exit("Can\'t create context");
	cldata->command_queue = clCreateCommandQueue(cldata->context,
		cldata->device_id, 0, &cldata->ret);
	if (cldata->ret)
		cl_exit("Can\'t create command queue");
}

static void				opencl_compile_kernel(t_cldata *cldata)
{
	const char		filename[] = "eval.cl";
	char			*source_str;
	int				fd;

	cldata->program = NULL;
	cldata->kernel = NULL;
	fd = open(filename, O_RDONLY);
	source_str = malloc(MAX_SOURCE_SIZE);
	read(fd, source_str, MAX_SOURCE_SIZE);
	close(fd);
	cldata->program = clCreateProgramWithSource(cldata->context, 1,
		(const char**)&source_str, NULL, &cldata->ret);
	if (cldata->ret)
		cl_exit("Can\'t create program from source");
	cldata->ret = clBuildProgram(cldata->program, 1, &cldata->device_id,
		NULL, NULL, NULL);
	if (cldata->ret)
	{
		char ret1[100000];
		ft_memset(ret1, 0, 100000);
		clGetProgramBuildInfo(cldata->program, cldata->device_id, CL_PROGRAM_BUILD_LOG,
								100000, &ret1, NULL);
		write(1, ret1, 100000);
		write(1, "\n", 1);
		// free(ret);
		cl_exit("Can\'t build program");
	}
	cldata->kernel = clCreateKernel(cldata->program, "eval", &cldata->ret);
	if (cldata->ret)
		cl_exit("Can\'t create kernel");
}

static void				opencl_create_buf(t_cldata *cldata)
{
	/* создать буфер */
	cldata->buf = clCreateBuffer(cldata->context, CL_MEM_WRITE_ONLY,
								WIDTH * HEIGHT * sizeof(int), NULL,
								&cldata->ret);
	if (cldata->ret)
		cl_exit("Can\'t create buffer");
}

t_cldata				*opencl_init(void)
{
	t_cldata		*cldata;

	cldata = malloc(sizeof(t_cldata));
	ft_assert(cldata != NULL, "Can\'t allocate cldata");
	opencl_create_infrastruct(cldata);
	opencl_compile_kernel(cldata);
	opencl_create_buf(cldata);
	cldata->threads = 200;
	return (cldata);
}