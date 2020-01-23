/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graph_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 17:56:11 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/20 17:56:12 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

void			ft_free_split(char **split)
{
	int			i;

	i = -1;
	while (split[++i])
		free(split[i]);
	free(split);
}
t_move			*create_move(char *str)
{
	char		**split;
	t_move		*ret;

	if (!str)
	{
		if (!(ret = malloc(sizeof(t_move))))
			ft_error("Malloc error");
		ret->nb = -1;
		ret->node = NULL;
		return (ret);
	}
	split = ft_strsplit(str, '-');
	if (!split || !split[0] || !split[1] || split[2])
		ft_error("Ant move error");
	if (!(ret = malloc(sizeof(t_move))))
		ft_error("Malloc error");
	ret->nb = ft_atoi(split[0] + 1) - 1;
	ret->node = split[1];
	free(split[0]);
	free(split);
	return (ret);
}

void			fill_movement(t_graph *g)
{
	char		**split;
	int			i;

	if (!g->str)
		ft_error("Input error");
	g->str = g->str->next;
	while (g->str)
	{
		split = ft_strsplit(g->str->content, ' ');
		i = -1;
		while (split[++i])
			g->movement = list_add_back(g->movement, create_move(split[i]));
		g->movement = list_add_back(g->movement, create_move(split[i]));
		g->str = g->str->next;
		ft_free_split(split);
	}
}
