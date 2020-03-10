#ifndef OPENCL_H
# define OPENCL_H

# define CL_TARGET_OPENCL_VERSION 220
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define KERNEL_NAME "eval"
# define KERNEL_FILE "eval.cl"

typedef struct			s_cldata
{
	int					threads;
	cl_uint				num_platforms;
	cl_device_id		device_id;
	cl_uint				num_devices;
	cl_platform_id		platform_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buf;
}						t_cldata;

t_cldata				*opencl_init(void);

#endif