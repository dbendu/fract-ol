/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_fractol.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 22:56:05 by user              #+#    #+#             */
/*   Updated: 2020/04/22 12:29:59 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	reset_fractol(t_data *data)
{
	data->iters = 50;
	data->camera.x = 0;
	data->camera.y = 0;
	data->camera.zoom = 140;
	data->mouse.x = WIDTH / 2;
	data->mouse.y = HEIGHT / 2;
}
