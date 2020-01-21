/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:25:28 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/21 15:48:13 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

void			move_texture(double *angle, int i, t_graph *g, t_sdl *s)
{
	if (s->curr_time > s->start_time + ANIM_S)
	{
		g->ants[i].start_pos = g->ants[i].end_pos;
		g->ants[i].curr_pos = (SDL_Point)
				{g->ants[i].end_pos->x, g->ants[i].end_pos->y};
		g->ants[i].moving = 0;
	}
	else
	{
		*angle = calc_angle(*g->ants[i].start_pos, *g->ants[i].end_pos);
		s->factor = (double)(s->curr_time - s->start_time) / ANIM_S;
		translate_point(&g->ants[i].curr_pos,
				*g->ants[i].start_pos, *g->ants[i].end_pos, s->factor);
	}
}

void			put_ants(t_graph *g, t_sdl *s)
{
	double		angle;
	int			still_move;
	int			i;

	i = -1;
	still_move = 0;
	while (++i < g->lem_count)
	{
		angle = 0;
		if (g->ants[i].moving)
		{
			still_move++;
			move_texture(&angle, i, g, s);
		}
		else
			g->ants[i].curr_pos = *g->ants[i].start_pos;
		texture_render_ex(g->ants[i].curr_pos, angle, &s->ant, s);
	}
	s->moving = (still_move > 0);
}

void			draw_strokes(t_graph *graph, t_sdl *sdl)
{
	t_list		*lst;
	t_stroke	*stroke;

	lst = graph->strokes;
	while (lst)
	{
		stroke = lst->content;
		draw_line(*stroke->p1, *stroke->p2, sdl);
		SDL_RenderDrawLine(sdl->ren, stroke->p1->x,
				stroke->p1->y, stroke->p2->x, stroke->p2->y);
		lst = lst->next;
	}
}

void			put_text(int x, int y, const char *text, t_sdl *sdl)
{
	SDL_Surface	*surf;
	SDL_Rect	rect;

	if (sdl->message)
		SDL_DestroyTexture(sdl->message);
	if (!(surf = TTF_RenderText_Solid(sdl->font, text,
			(SDL_Color){0xFF, 0x0, 0x0})))
		ft_error(SDL_GetError());
	if (!(sdl->message = SDL_CreateTextureFromSurface(sdl->ren, surf)))
		ft_error(SDL_GetError());
	SDL_FreeSurface(surf);
	rect = (SDL_Rect){x, y, 75, 75};
	SDL_RenderCopy(sdl->ren, sdl->message, NULL, &rect);
}

void			build_houses(t_texture *txt, t_graph *graph, t_sdl *sdl)
{
	t_list		*lst;
	t_node		*node;

	lst = graph->node;
	while (lst)
	{
		node = lst->content;
		texture_render((SDL_Point){node->point.x - txt->width / 2,
					node->point.y - txt->height / 2}, txt, sdl);
		lst = lst->next;
	}
	node = graph->node->content;
	put_text(node->point.x - 40, node->point.y - 50, node->name, sdl);
	node = (list_at(graph->node, list_length(graph->node)))->content;
	put_text(node->point.x - 40, node->point.y - 50, node->name, sdl);
}
