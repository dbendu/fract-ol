#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include "opencl.h"
#include "mlx_defines.h"
#include "libft.h"

#define MAX_SOURCE_SIZE	10000

static void			cl_exit(char *msg)
{
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	exit(0);
}

static void			opencl_create_infrastruct(t_cldata *cldata)
{
	cl_int			ret;

	ret = clGetPlatformIDs(1, &cldata->platform_id,
		&cldata->num_platforms);
	if (ret)
		cl_exit("Can\'t get platforms");
	ret = clGetDeviceIDs(cldata->platform_id, CL_DEVICE_TYPE_GPU, 1,
		&cldata->device_id, &cldata->num_devices);
	if (ret)
		cl_exit("Can\'t get devices");
	cldata->context = clCreateContext(NULL, 1, &cldata->device_id, NULL, NULL,
		&ret);
	if (ret)
		cl_exit("Can\'t create context");
	cldata->command_queue = clCreateCommandQueueWithProperties(cldata->context,
		cldata->device_id, 0, &ret);
	if (ret)
		cl_exit("Can\'t create command queue");
}

static char			*opencl_read_kernel_from_file(void)
{
	char			*source_str;
	int				fd;
	ssize_t			read_ret;

	fd = open(KERNEL_FILE, O_RDONLY);
	if (fd < 0)
		cl_exit("Can\'t open file");
	source_str = malloc(MAX_SOURCE_SIZE);
	read_ret = read(fd, source_str, MAX_SOURCE_SIZE);
	close(fd);
	source_str[read_ret] = '\0';
	return (source_str);
}

static void				opencl_compile_kernel(t_cldata *cldata, char *source)
{
	cl_int				ret;
	size_t				error_msg_len;

	cldata->program = clCreateProgramWithSource(cldata->context, 1,
		(const char**)&source, NULL, &ret);
	if (ret)
		cl_exit("Can\'t create program from source");
	ret = clBuildProgram(cldata->program, 1, &cldata->device_id,
		"-I includes", NULL, NULL);
	if (ret)
	{
		char buf[10000];
		clGetProgramBuildInfo(cldata->program, cldata->device_id,
				CL_PROGRAM_BUILD_LOG, MAX_SOURCE_SIZE, &buf, &error_msg_len);
		write(1, buf, error_msg_len);
		write(1, "\n", 1);
		cl_exit("Can\'t build program");
	}
	cldata->kernel = clCreateKernel(cldata->program, "eval", &ret);
	if (ret)
		cl_exit("Can\'t create kernel");
}

static void				opencl_create_buf(t_cldata *cldata)
{
	cl_int				ret;

	/* создать буфер */
	cldata->buf = clCreateBuffer(cldata->context, CL_MEM_WRITE_ONLY,
								WIDTH * HEIGHT * sizeof(int), NULL,
								&ret);
	if (ret)
		cl_exit("Can\'t create buffer");
}

t_cldata				*opencl_init(void)
{
	t_cldata		*cldata;
	char			*kernel_src;

	cldata = malloc(sizeof(t_cldata));
	ft_assert(cldata != NULL, "Can\'t allocate cldata");
	opencl_create_infrastruct(cldata);
	kernel_src = opencl_read_kernel_from_file();
	opencl_compile_kernel(cldata, kernel_src);
	free(kernel_src);
	opencl_create_buf(cldata);
	cldata->threads = 200;
	return (cldata);
}
