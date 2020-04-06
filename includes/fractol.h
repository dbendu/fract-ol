/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 22:15:45 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/06 13:19:23 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft.h"
# include "data.h"
# include "mlx.h"

void			draw(t_data *data);

int				key_press(int button, t_data *data);
int				mouse_press(int button, int x, int y, t_data *data);
int				mouse_release(int button, int x, int y, t_data *data);
int				mouse_move(int x, int y, t_data *data);

void			reset(t_data *data);

void			fractol_exit(t_data *data);

#endif
