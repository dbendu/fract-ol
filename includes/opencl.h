/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 22:16:12 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/06 11:31:34 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPENCL_H
# define OPENCL_H

# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# define CL_TARGET_OPENCL_VERSION 220
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# define KERNEL_NAME "eval"
# define KERNEL_FILE "srcs/eval.cl"

typedef struct			s_cldata
{
	cl_uint				num_platforms;
	cl_device_id		device_id;
	cl_uint				num_devices;
	cl_platform_id		platform_id;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				buf;
	size_t				work_size;
}						t_cldata;

t_cldata				*opencl_init(void);

#endif
