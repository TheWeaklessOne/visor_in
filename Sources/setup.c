/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:29:25 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 18:29:26 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

void			create_ants(t_graph *graph)
{
	int			i;
	t_node		*node;

	if (!(graph->ants = malloc(sizeof(t_ant) * graph->lem_count)))
		ft_error("Malloc error");
	i = -1;
	node = graph->node->content;
	while (++i < graph->lem_count)
		graph->ants[i] = (t_ant){
				.start_pos = &node->point,
				.curr_pos = node->point,
				.end_pos = &node->point,
				.moving = 0};
}

void			sdl_init(t_sdl *sdl)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return (ft_error(SDL_GetError()));
	if (!(sdl->win = SDL_CreateWindow("Visor_in", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)))
		return (ft_error(SDL_GetError()));
	if (!(sdl->ren = SDL_CreateRenderer(sdl->win, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		return (ft_error(SDL_GetError()));
	SDL_SetRenderDrawColor(sdl->ren, 0xFF, 0xFF, 0xFF, 0xFF);
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		return (ft_error(SDL_GetError()));
	if (TTF_Init() == -1)
		return (ft_error(SDL_GetError()));
	sdl->message = NULL;
	sdl->mouse = (t_mouse){(SDL_Point){0, 0}, (SDL_Point){0, 0}, 0};
	sdl->view.zoom = 1.0f;
	sdl->view.x_max = 0;
	sdl->view.y_max = 0;
	sdl->view.x_min = INT32_MAX;
	sdl->view.y_min = INT32_MAX;
	sdl->moving = 0;
	sdl->running = 1;
}

void			sdl_quit(t_sdl *sdl)
{
	SDL_DestroyRenderer(sdl->ren);
	SDL_DestroyWindow(sdl->win);
	sdl->win = NULL;
	sdl->ren = NULL;
	IMG_Quit();
	TTF_Quit();
	SDL_Quit();
}
