#ifdef cl_khr_fp64
    #pragma OPENCL EXTENSION cl_khr_fp64 : enable
#elif defined(cl_amd_fp64)
    #pragma OPENCL EXTENSION cl_amd_fp64 : enable
#else
    #error "Double precision floating point not supported by OpenCL implementation."
#endif

#include "mlx_defines.h"
#include "fractols_list.h"

typedef struct			s_complex
{
	double			re;
	double			im;
}						t_complex;

t_complex		complex_add(const t_complex *c1, const t_complex *c2)
{
	t_complex	res;

	res.re = c1->re + c2->re;
	res.im = c1->im + c2->im;
	return (res);
}

t_complex		complex_div(const t_complex *c1, const t_complex *c2)
{
	t_complex	res;

	res.re = (c1->re * c2->re + c1->im * c2->im) /
				(c2->re * c2->re + c2->im * c2->im);
	res.im = (c2->re * c1->im - c2->im * c1->re) /
				(c2->re * c2->re + c2->im * c2->im);
	return (res);
}

t_complex		complex_init(long double re, long double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

t_complex		complex_mult(const t_complex *c1, const t_complex *c2)
{
	t_complex	res;

	res.re = c1->re * c2->re - c1->im * c2->im;
	res.im = c1->re * c2->im + c2->re * c1->im;
	return (res);
}

t_complex		complex_pow2(const t_complex *c)
{
	t_complex	res;

	res.re = c->re * c->re - c->im * c->im;
	res.im = 2 * c->re * c->im;
	return (res);
}

t_complex			complex_pow3(const t_complex *c)
{
	t_complex		pow2;

	pow2 = complex_pow2(c);
	return (complex_mult(c, &pow2));
}

t_complex			complex_sub(const t_complex *c1, const t_complex *c2)
{
	t_complex		res;

	res.re = c1->re - c2->re;
	res.im = c1->im - c2->im;
	return (res);
}












static int		mandelbrot(int x, int y, int max_iters, double x_offset, double y_offset, float zoom)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - WIDTH / 2) / zoom + (long double)x_offset;
	c.im = (HEIGHT / 2 - y) / zoom + (long double)y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters && point.re * point.re + point.im * point.im <= 4)
	{
		temp = point;
		point.re = temp.re * temp.re - temp.im * temp.im + c.re;
		point.im = 2 * temp.re * temp.im + c.im;
		++iter;
	}
	return (iter);
}

static int		mandelbar(int x, int y, int max_iters, double x_offset, double y_offset, float zoom)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - WIDTH / 2) / zoom + (long double)x_offset;
	c.im = (HEIGHT / 2 - y) / zoom + (long double)y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters)
	{
		if (point.re * point.re + point.im * point.im > 4)
			break ;
		temp = point;
		point.re = temp.re * temp.re - temp.im * temp.im + c.re;
		point.im = -2 * temp.re * temp.im + c.im;
		++iter;
	}
	return (iter);
}

__kernel void	eval(__global int *data, double x_offset, double y_offset, float zoom, int iters, int fractol_type)
{
	int				id;
	int				iter;
	int				x;
	int				y;

	id = get_global_id(0);
	x = id / HEIGHT;
	y = id % HEIGHT;


	switch (fractol_type)
	{
	case MANDELBROT:
		iter = mandelbrot(x, y, iters, x_offset, y_offset, zoom);
		break ;
	case MANDELBAR:
		iter = mandelbar(x, y, iters, x_offset, y_offset, zoom);
		break ;
	}

	if (iter < iters)
		data[y * WIDTH + x] = 0xFFFFFF;
	else
		data[y * WIDTH + x] = 0x0;
}
