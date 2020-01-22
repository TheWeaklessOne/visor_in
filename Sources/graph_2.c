/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:25:19 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 17:25:21 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

void			check_all(t_graph *graph)
{
	t_node		*a;
	t_node		*b;
	t_list		*tmp;
	t_list		*tmp_2;

	if (!graph->strokes)
		ft_error("Room link error");
	tmp = graph->node;
	while (tmp->next)
	{
		a = tmp->content;
		if (a->name[0] == 'L' || a->name[0] == '#')
			ft_error("Room name error");
		tmp_2 = tmp->next;
		while (tmp_2)
		{
			b = tmp_2->content;
			if (!ft_strcmp(a->name, b->name))
				ft_error("Room name error");
			tmp_2 = tmp_2->next;
		}
		tmp = tmp->next;
	}
}

void			fill_stroke(t_node *sae[2], t_graph *graph)
{
	char		**s;

	if (!sae[0] || !sae[1])
		ft_error("Start and\\or end error");
	while (graph->str && ft_strcmp(graph->str->content, ""))
	{
		if (!(s = ft_strsplit(graph->str->content, '-')) || !s[0]
				|| !s[1] || s[2])
			ft_error("Input error");
		graph->strokes = list_add_back(graph->strokes,
				create_stroke(s[0], s[1], graph));
		graph->str = graph->str->next;
		free(s[0]);
		free(s[1]);
		free(s);
	}
	fill_movement(graph);
}

void			sae_stuff(int type, t_node *sae[2], t_graph *g)
{
	while (check_type((g->str = g->str->next)->content))
		if (check_type(g->str->content) != -1)
			ft_error("Input error");
	if (type == 1 && sae[0])
		ft_error("Double start room");
	else if (type == 2 && sae[1])
		ft_error("Double end room");
	sae[type == 2] = create_node(g->str->content);
}

void			fill_node(t_graph *g)
{
	t_node		*sae[2];
	int			type;

	sae[0] = NULL;
	sae[1] = NULL;
	while (g->str->next && *(char*)(g->str->content) == '#')
		g->str = g->str->next;
	if ((g->lem_count = ft_atoi(g->str->content)) <= 0)
		ft_error("Lem count error");
	while ((g->str = g->str->next))
	{
		if ((type = check_type(g->str->content)) == -1)
			continue ;
		if (type == -2)
			break ;
		if (type)
		{
			sae_stuff(type, sae, g);
		}
		else
			g->node = list_add_back(g->node, create_node(g->str->content));
	}
	g->node = list_add_front(g->node, sae[0]);
	g->node = list_add_back(g->node, sae[1]);
	fill_stroke(sae, g);
}

void			read_all(t_graph *graph)
{
	char		*str;

	str = NULL;
	while (gnl(0, &str))
		if (check_type(str) != -1)
			graph->str = list_add_back(graph->str, str);
	graph->str_head = graph->str;
}
