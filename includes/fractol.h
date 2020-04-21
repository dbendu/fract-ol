/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 22:15:45 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/21 22:58:35 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <SDL2/SDL.h>

# include "libft.h"
# include "data.h"

# define WIDTH	1000
# define HEIGHT	1000

t_data		init_data(void);
void		quit(const t_data *data);

void		draw(t_data *data);
void		reset_fractol(t_data *data);

void		key_press(t_data *data, SDL_Keycode button);

void		mouse_press(t_data *data, const SDL_MouseButtonEvent *event);
void		mouse_release(t_data *data, int button);
void		mouse_move(t_data *data, int x, int y);
void		mouse_wheel(t_data *data, int direction);

#endif
