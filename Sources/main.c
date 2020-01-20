/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:25:24 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 17:25:25 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

void			move_ants(t_graph *graph)
{
	t_move		*move;
	t_move		*to_free;
	t_list		*lst;

	while (graph->movement)
	{
		move = graph->movement->content;
		if (move->nb == -1)
		{
			lst = graph->movement;
			graph->movement = graph->movement->next;
			free(lst->content);
			free(lst);
			break ;
		}
		if (!(graph->ants[move->nb].end_pos = find_by_name(move->node, graph)))
			ft_error("Node name error");
		graph->ants[move->nb].moving = 1;
		lst = graph->movement;
		graph->movement = graph->movement->next;
		to_free = lst->content;
		free(to_free->node);
		free(lst->content);
		free(lst);
	}
}

void			event_handler_2(SDL_Event e, t_graph *graph, t_sdl *sdl)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			sdl->running = 0;
		if (e.key.keysym.sym == SDLK_SPACE && !sdl->moving)
		{
			move_ants(graph);
			sdl->start_time = sdl->curr_time;
			sdl->moving = 1;
		}
	}
	else if (e.type == SDL_QUIT)
		sdl->running = 0;
}

void			event_handler(SDL_Event e, t_graph *graph, t_sdl *sdl)
{
	if ((e.type == SDL_MOUSEBUTTONDOWN ||
		e.type == SDL_MOUSEBUTTONUP) && !sdl->moving)
		sdl->mouse.pressed = e.type == SDL_MOUSEBUTTONDOWN;
	else if (e.type == SDL_MOUSEMOTION && !sdl->moving)
	{
		sdl->mouse.old_pos = sdl->mouse.curr_pos;
		if (!sdl->moving)
			SDL_GetMouseState(&sdl->mouse.curr_pos.x, &sdl->mouse.curr_pos.y);
		if (sdl->mouse.pressed)
			translate_pos(sdl->mouse.curr_pos.x - sdl->mouse.old_pos.x,
					sdl->mouse.curr_pos.y - sdl->mouse.old_pos.y, graph);
	}
	else if (e.type == SDL_MOUSEWHEEL && !sdl->moving)
	{
		if (e.wheel.y > 0)
			sdl->view.zoom -= 0.01f;
		else if (e.wheel.y < 0)
			sdl->view.zoom += 0.01f;
		SDL_RenderSetScale(sdl->ren, sdl->view.zoom, sdl->view.zoom);
	}
	else
		event_handler_2(e, graph, sdl);
}

int				main(void)
{
	t_graph		graph;
	t_sdl		sdl;
	SDL_Event	e;

	init_graph(&graph);
	sdl_init(&sdl);
	translate_to_screen(&graph, &sdl);
	create_ants(&graph);
	texture_load("Components/ant.png", &sdl.ant, &sdl);
	texture_load("Components/house.png", &sdl.house, &sdl);
	while (sdl.running)
	{
		sdl.curr_time = SDL_GetTicks();
		while (SDL_PollEvent(&e))
			event_handler(e, &graph, &sdl);
		SDL_SetRenderDrawColor(sdl.ren, 0x30, 0x30, 0x30, 0xFF);
		SDL_RenderClear(sdl.ren);
		SDL_SetRenderDrawColor(sdl.ren, 0xFF, 0x00, 0x00, 0x00);
		draw_strokes(&graph, &sdl);
		put_ants(&graph, &sdl);
		build_houses(&sdl.house, &graph, &sdl);
		SDL_RenderPresent(sdl.ren);
	}
	sdl_quit(&sdl);
	exit(0);
}
