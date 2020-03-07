typedef struct		s_complex
{
	double		re;
	double		im;
}					t_complex;

int setup_color(int iter, int iters)
{
	float t = (double)iter / (double)iters;

	int red = (int)(9 * (1 - t) * pow(t, 3) * 255);
	int green = (int)(15 * pow((1 - t), 2) * pow(t, 2) * 255);
	int blue = (int)(8.5 * pow((1 - t), 3) * t * 255);
	return ((red << 16) + (green << 8) + blue);
}

__kernel void	eval(__global int *data, int width, int height, int threads, double x_offset, double y_offset, float zoom, int iters)
{
	int				id;
	int				iter;
	int				x;
	int				y;
	t_complex		c;
	t_complex		point;
	t_complex		temp;

	id = get_global_id(0);
	y = id / height;
	x = id % height;

	iter = 0;
	c.re = (x - width / 2) / zoom + x_offset;
	c.im = (height / 2 - y) / zoom + y_offset;
	point = c;
	while (iter < iters && point.re * point.re + point.im * point.im <= 4)
	{
		temp = point;
		point.re = temp.re * temp.re - temp.im * temp.im + c.re;
		point.im = 2 * temp.re * temp.im + c.im;
		++iter;
	}
	if (iter < iters)
		data[y * width + x] = 0xFFFFFF;
//		data[y * width + x] = setup_color(iter, iters);
	else
		data[y * width + x] = 0x0;
//		printf("%d\n", data[y * width + x]);
}
