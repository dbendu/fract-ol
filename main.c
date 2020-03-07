#include <math.h>
#include <stdio.h>

#include "fractol.h"
#include "mlx.h"
#include "mlx_defines.h"

t_data	data_create(void)
{
	t_data data;

	data.wnd.mlxptr = mlx_init();
	data.wnd.wndptr = mlx_new_window(data.wnd.mlxptr, WIDTH, HEIGHT,
									"fract'ol");
	data.wnd.imgptr = mlx_new_image(data.wnd.mlxptr, WIDTH, HEIGHT);
	data.wnd.img = (int*)mlx_get_data_addr(data.wnd.imgptr, &data.wnd.bytes,
									&data.wnd.size_line, &data.wnd.endian);
	data.wnd.bytes /= 8;
	data.camera.x = 0;
	data.camera.y = 0;
	data.camera.zoom = 100;
	data.iters = 50;
	data.mouse.x = WIDTH / 2;
	data.mouse.y = HEIGHT / 2;
	data.width = WIDTH;
	data.height = HEIGHT;
	data.cldata = opencl_init();
	return (data);
}

int main(void)
{
	t_data		data;

	data = data_create();

	draw(&data);

	mlx_hook(data.wnd.wndptr, 2, 1L << 0, key_press, &data);
	mlx_hook(data.wnd.wndptr, 4, 1L << 2, mouse_press, &data);
	mlx_hook(data.wnd.wndptr, 5, 1L << 3, mouse_release, &data);
	mlx_hook(data.wnd.wndptr, 6, 1L << 13, mouse_move, &data);

	mlx_loop(data.wnd.mlxptr);

	return (0);
}