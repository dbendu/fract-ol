#ifndef FRACTOL_H
# define FRACTOL_H

#include "libft.h"
#include "data.h"

void			draw(t_data *data);

int				key_press(int button, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				mouse_release(int button, int x, int y, t_data *data);
int				mouse_move(int x, int y, t_data *data);

void			reset(t_data *data);

#endif
