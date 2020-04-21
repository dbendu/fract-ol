/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 16:26:19 by dbendu            #+#    #+#             */
/*   Updated: 2020/04/21 22:55:57 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	sdl_cycle(t_data *data)
{
	t_bool		quit;
	SDL_Event	event;

	quit = FALSE;
	while (quit != TRUE)
	{
		SDL_WaitEvent(&event);
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				quit = TRUE;
			else
				key_press(data, event.key.keysym.sym);
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_press(data, &event.button);
		else if (event.type == SDL_MOUSEBUTTONUP)
			mouse_release(data, event.button.button);
		else if (event.type == SDL_MOUSEMOTION)
			mouse_move(data, event.motion.x, event.motion.y);
		else if (event.type == SDL_MOUSEWHEEL)
			mouse_wheel(data, event.wheel.y);
		else if (event.type == SDL_QUIT)
			quit = TRUE;
	}
}

int			main(void)
{
	t_data	data;

	data = init_data();
	draw(&data);
	sdl_cycle(&data);
	quit(&data);
	return (0);
}
