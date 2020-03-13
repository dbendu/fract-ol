#include "mlx_defines.h"
#include "fractols_list.h"
#include "color_schemes.h"

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

t_complex		complex_init(double re, double im)
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

double		complex_abs(const t_complex *c)
{
	return (sqrt(c->re * c->re + c->im * c->im));
}











// main cycle may look like this:
//
// while (iter < max_iters && pow(point.re, 2) + pow(point.im, 2) <= 4)
// {
//     point = pow(point, 2);
//     point.re += c.re;
//     point.im += c.im;
//     ++iter;
// }

static int		mandelbrot(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - WIDTH / 2) / zoom + x_offset;
	c.im = (HEIGHT / 2 - y) / zoom + y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters)
	{
		temp.re = point.re * point.re;
		temp.im = point.im * point.im;
		if (temp.re + temp.im > 4)
			break ;
		point.im = 2 * point.re * point.im + c.im;
		point.re = temp.re - temp.im + c.re;
		++iter;
	}
	return (iter);
}


// main cycle may look like this:
//
// while (iter < max_iters && pow(point.re, 2) + pow(point.im, 2) <= 4)
// {
//     point = pow(point, 2);
//     point.re += c.re;
//     point.im = -point.im + c.im;
//     ++iter;
// }

static int		mandelbar(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - WIDTH / 2) / zoom + x_offset;
	c.im = (HEIGHT / 2 - y) / zoom + y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters)
	{
		temp.re = point.re * point.re;
		temp.im = point.im * point.im;
		if (temp.re + temp.im > 4)
			break ;
		point.im = -2 * point.re * point.im + c.im;
		point.re = temp.re - temp.im + c.re;
		++iter;
	}
	return (iter);
}

static int		julia(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom,
							double julia_re, double julia_im)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - WIDTH / 2) / zoom + x_offset;
	c.im = (HEIGHT / 2 - y) / zoom + y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters)
	{
		temp.re = point.re * point.re;
		temp.im = point.im * point.im;
		if (temp.re + temp.im > 4)
			break ;
		point.im = 2 * point.re * point.im + julia_im;
		point.re = temp.re - temp.im + julia_re;
		point.re += julia_re;
		point.im += julia_im;
		++iter;
	}
	return (iter);
}


// main cycle may look like this:
//
// while (iter < max_iters && pow(point.re, 2) + pow(point.im, 2) <= 4)
// {
//     point = pow(point, 2);
//     point.re += c.re;
//     point.im += c.im;
//     c.re = c.re / 2 + point.re;
//     c.im = c.im / 2 + point.im;
//     ++iter;
// }

static int		spider(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;


	c.re = (x - WIDTH / 2) / zoom + x_offset;
	c.im = (HEIGHT / 2 - y) / zoom + y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters)
	{
		temp.re = point.re * point.re;
		temp.im = point.im * point.im;
		if (temp.re + temp.im > 4)
			break ;
		point.im = 2 * point.re * point.im + c.im;
		point.re = temp.re - temp.im + c.re;
		c.re = c.re / 2 + point.re;
		c.im = c.im / 2 + point.im;
		++iter;
	}
	return (iter);
}

static int 		setup_color(int iter, int max_iters, int color_scheme)
{
	int			red;
	int			blue;
	int			green;
	double		n;

	n = (double)iter / (double)max_iters;
	red = (int)(9 * (1 - n) * pow(n, 3) * 255);
	green = (int)(15 * pow((1 - n), 2) * pow(n, 2) * 255);
	blue = (int)(8.5 * pow((1 - n), 3) * n * 255);

	if (color_scheme == BLACK_N_WHITE)
		return (iter == max_iters ? BLACK : WHITE);
	else if (color_scheme == RGB)
		return (red << 16 | green << 8 | blue);
	else if (color_scheme == RBG)
		return (red << 16 | blue << 8 | green);
	else if (color_scheme == GBR)
		return (green << 16 | blue << 8 | red);
	else if (color_scheme == GRB)
		return (green << 16 | red << 8 | blue);
	else if (color_scheme == BRG)
		return (blue << 16 | red << 8 | green);
	else if (color_scheme == BGR)
		return (blue << 16 | green << 8 | red);
	else	// never used
		return (0);
}


__kernel void	eval(__global int *data, double x_offset, double y_offset, double zoom, int iters, int fractol_type,
																double julia_re, double julia_im, int color_scheme)
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
	case JULIA:
		iter = julia(x, y, iters, x_offset, y_offset, zoom, julia_re, julia_im);
		break ;
	case NEWTON:
		iter = spider(x, y, iters, x_offset, y_offset, zoom);
		break ;
	}

	if (iter < iters)
	//	data[y * WIDTH + x] = 0xFFFFFF;
		data[y * WIDTH + x] = setup_color(iter, iters, color_scheme);
	else
		data[y * WIDTH + x] = 0x0;
}
