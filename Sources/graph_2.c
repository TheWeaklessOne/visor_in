#include "../Includes/visor_in.h"

int				gnl(int fd, char **str)
{
	int		ret;

	if ((ret = get_nl(fd, str)) == -1 || !*str)
		ft_error("Input error");
	return (ret);
}

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
	while (graph->str)
	{
		if (!(s = ft_strsplit(graph->str->content, '-')) || !s[0] || !s[1] || s[2])
			ft_error("Input error");
		graph->strokes = list_add_back(graph->strokes, create_stroke(s[0], s[1], graph));
		graph->str = graph->str->next;
	}
}

void			fill_node(t_graph *graph)
{
	t_node		*sae[2];
	int			type;

	sae[0] = NULL;
	sae[1] = NULL;
	while (graph->str->next && *(char*)(graph->str->content) == '#')
		graph->str = graph->str->next;
	if ((graph->lem_count = ft_atoi(graph->str->content)) <= 0)
		ft_error("Lem count error");
	while ((graph->str = graph->str->next))
	{
		if ((type = check_type(graph->str->content)) == -1)
			continue ;
		if (type == -2)
			break ;
		if (type)
		{
			while (check_type((graph->str = graph->str->next)->content))
				if (check_type(graph->str->content) != -1)
					ft_error("Input error");
			sae[type == 2] = create_node(graph->str->content);
		}
		else
			graph->node = list_add_back(graph->node, create_node(graph->str->content));
	}
	graph->node = list_add_front(graph->node, sae[0]);
	graph->node = list_add_back(graph->node, sae[1]);
	fill_stroke(sae, graph);
}

void			read_all(t_graph *graph)
{
	char		*str;

	str = NULL;
	while (gnl(0, &str))
		graph->str = list_add_back(graph->str, str);
}
