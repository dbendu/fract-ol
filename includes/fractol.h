#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft.h"
#include "opencl.h"

# define ZOOM			1.2

typedef struct			s_wnd
{
	void				*mlxptr;
	void				*wndptr;
	void				*imgptr;
	int					*img;
	int					bytes;
	int					size_line;
	int					endian;
}						t_wnd;

typedef struct			s_camera
{
	double				x;
	double				y;
	float				zoom;
}						t_camera;

typedef struct			s_mouse
{
	int					x;
	int					y;
	t_bool				is_left_button_active;
	t_bool				is_right_button_active;
}						t_mouse;

typedef struct			s_data
{
	t_wnd				wnd;
	t_camera			camera;
	t_mouse				mouse;
	t_cldata			*cldata;
	int					iters;
	int					fractol_type;
	double				julia_re;
	double				julia_im;
}						t_data;

void			draw(t_data *data);

int				key_press(int button, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				mouse_release(int button, int x, int y, t_data *data);
int				mouse_move(int x, int y, t_data *data);

#endif
