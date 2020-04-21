#include "fractols_list.h"
#include "color_schemes.h"

# define abs(x) ((x) > 0 ? (x) : (-x))


/*******************************************************************************
						COMPLEX NUMBERS AND OPERATIONS
*******************************************************************************/

typedef struct			s_complex
{
	double			re;
	double			im;
}						t_complex;


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





/*******************************************************************************
								MANDELBROT
*******************************************************************************/

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

	c.re = (x - 1000 / 2) / zoom + x_offset;
	c.im = (1000 / 2 - y) / zoom + y_offset;
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




/*******************************************************************************
									MANDELBAR
*******************************************************************************/

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

	c.re = (x - 1000 / 2) / zoom + x_offset;
	c.im = (1000 / 2 - y) / zoom + y_offset;
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




/*******************************************************************************
									JULIA
*******************************************************************************/

// main cycle may look like this:
//
// while (iter < max_iters && pow(point.re, 2) + pow(point.im, 2) <= 4)
// {
//     point = pow(point, 2);
//     point.re += f(mouse.x);
//     point.im += f(mouse.y);
//     ++iter;
// }

static int		julia(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom,
							double julia_re, double julia_im)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - 1000 / 2) / zoom + x_offset;
	c.im = (1000 / 2 - y) / zoom + y_offset;
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
		++iter;
	}
	return (iter);
}




/*******************************************************************************
									SPIDER
*******************************************************************************/

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


	c.re = (x - 1000 / 2) / zoom + x_offset;
	c.im = (1000 / 2 - y) / zoom + y_offset;
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




/*******************************************************************************
									NEWTON
*******************************************************************************/

// formula:
//
//              Zi^3 - 1
// Zi+1 = Zi - ----------, Zo = c
//               3Zi^2

static int		newton(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom)
{
	int				iter;
	t_complex		point;
	t_complex		numerator;
	t_complex		denominator;
	t_complex		temp;
	t_complex		roots[3];
	const double	eps = 0.0000000001;

	roots[0] = complex_init(1, 0);
	roots[1] = complex_init(-0.5, 0.86602540378);
	roots[2] = complex_init(-0.5, -0.86602540378);
	point.re = (x - 1000 / 2) / zoom + x_offset;
	point.im = (1000 / 2 - y) / zoom + y_offset;
	iter = 0;
	while (iter < max_iters)
	{
		numerator = complex_pow3(&point);
		numerator.re -= 1;
		denominator = complex_pow2(&point);
		denominator.re *= 3;
		denominator.im *= 3;

		temp = complex_div(&numerator, &denominator);
		point = complex_sub(&point, &temp);
		for (int i = 0; i < 3; ++i)
		{
			temp = complex_sub(&point, &roots[i]);
			if (abs(temp.re) < eps && abs(temp.im) < eps)
				return (iter);
		}
		++iter;
	}
	return (iter);
}




/*******************************************************************************
								BURNING SHIP
*******************************************************************************/

static int		burning_ship(int x, int y, int max_iters,
							double x_offset, double y_offset, double zoom)
{
	int			iter;
	t_complex	point;
	t_complex	c;
	t_complex	temp;

	c.re = (x - 1000 / 2) / zoom + x_offset;
	c.im = (1000 / 2 - y) / zoom + y_offset;
	point = c;
	iter = 0;
	while (iter < max_iters)
	{
		temp.re = point.re * point.re;
		temp.im = point.im * point.im;
		if (temp.re + temp.im > 4)
			break ;
		point.im = -2 * abs(point.re * point.im) + c.im;
		point.re = temp.re - temp.im + c.re;
		++iter;
	}
	return (iter);
}




/*******************************************************************************
								SELECT_COLOR
*******************************************************************************/

static int 		setup_color(int iter, int max_iters, int color_scheme)
{
	int			red;
	int			blue;
	int			green;
	double		n;

	n = (double)iter / max_iters;
	red =   (int)(9 * (1 - n) * pow(n, 3) * 255);
	green = (int)(15 * pow((1 - n), 2) * pow(n, 2) * 255);
	blue =  (int)(8.5 * pow((1 - n), 3) * n * 255);

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




/*******************************************************************************
									KERNEL
*******************************************************************************/

__kernel void	eval(__global int *data, double x_offset, double y_offset,
					double zoom, int max_iters, int fractol_type,
					double julia_re, double julia_im, int color_scheme)
{
	int				id;
	int				iter;
	int				x;
	int				y;

	id = get_global_id(0);
	x = id / 1000;
	y = id % 1000;

	switch (fractol_type)
	{
	case MANDELBROT:
		iter = mandelbrot(x, y, max_iters, x_offset, y_offset, zoom);
		break ;
	case MANDELBAR:
		iter = mandelbar(x, y, max_iters, x_offset, y_offset, zoom);
		break ;
	case JULIA:
		iter = julia(x, y, max_iters, x_offset, y_offset, zoom, julia_re, julia_im);
		break ;
	case SPIDER:
		iter = spider(x, y, max_iters, x_offset, y_offset, zoom);
		break ;
	case NEWTON:
		iter = newton(x, y, max_iters, x_offset, y_offset, zoom);
		break ;
	case BURNING_SHIP:
		iter = burning_ship(x, y, max_iters, x_offset, y_offset, zoom);
		break ;
	}
	data[y * 1000 + x] = setup_color(iter, max_iters, color_scheme);
}
