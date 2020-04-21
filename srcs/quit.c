/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user <user@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 22:56:02 by user              #+#    #+#             */
/*   Updated: 2020/04/21 22:58:56 by user             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	quit(const t_data *data)
{
	clReleaseContext(data->cldata->context);
	clReleaseCommandQueue(data->cldata->command_queue);
	clReleaseProgram(data->cldata->program);
	clReleaseKernel(data->cldata->kernel);
	clReleaseMemObject(data->cldata->buf);
	SDL_DestroyWindow(data->wnd.window);
	SDL_Quit();
}
