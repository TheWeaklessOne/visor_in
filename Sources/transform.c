/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:25:45 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 17:25:46 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

void		find_min_max(t_graph *graph, t_sdl *sdl)
{
	t_list	*tmp;
	t_node	*node;

	tmp = graph->node;
	while (tmp)
	{
		node = tmp->content;
		if (node->point.x < sdl->view.x_min)
			sdl->view.x_min = node->point.x;
		if (node->point.y < sdl->view.y_min)
			sdl->view.y_min = node->point.y;
		if (node->point.x > sdl->view.x_max)
			sdl->view.x_max = node->point.x;
		if (node->point.y > sdl->view.y_max)
			sdl->view.y_max = node->point.y;
		tmp = tmp->next;
	}
}

void		translate_point(SDL_Point *p, SDL_Point s, SDL_Point end, double f)
{
	double	t;

	t = 1.0 - f;
	p->x = (double)s.x * t + (double)end.x * f;
	p->y = (double)s.y * t + (double)end.y * f;
}

void		translate_to_screen(t_graph *graph, t_sdl *sdl)
{
	t_list	*tmp;
	t_node	*node;

	find_min_max(graph, sdl);
	tmp = graph->node;
	while (tmp)
	{
		node = tmp->content;
		node->point.x = (node->point.x - sdl->view.x_min)
						* SCREEN_WIDTH / sdl->view.x_max - sdl->view.x_min;
		node->point.y = (node->point.y - sdl->view.y_min)
						* SCREEN_HEIGHT / sdl->view.y_max - sdl->view.y_min;
		tmp = tmp->next;
	}
}

void		translate_pos(int x, int y, t_graph *graph)
{
	t_list	*lst;
	t_node	*node;

	lst = graph->node;
	while (lst)
	{
		node = lst->content;
		node->point.x += x;
		node->point.y += y;
		lst = lst->next;
	}
}
