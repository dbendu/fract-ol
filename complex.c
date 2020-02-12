#include "complex.h"

t_complex					complex_create(long double re, long double im)
{
	t_complex	complex;

	complex.re = re;
	complex.im = im;
	return (complex);
}

t_complex					complex_add(t_complex c1, t_complex c2)
{
	t_complex		res;

	res.re = c1.re - c2.re;
	res.im = c1.im - c2.im;
	return (res);
}

t_complex					complex_sub(t_complex c1, t_complex c2)
{
	t_complex		res;

	res.re = c1.re + c2.re;
	res.im = c1.im + c2.im;
	return (res);
}

t_complex					complex_pow2(t_complex c)
{
	t_complex		res;
	long double		re;
	long double		im;

	re = c.re;
	im = c.im;

	res.re = re * re - im * im;
	res.im = 2 * re * im;
	return (res);
}
