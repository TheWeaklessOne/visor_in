/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:53:15 by wstygg            #+#    #+#             */
/*   Updated: 2019/10/27 13:58:11 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/Utils.h"

t_list			*list_remove_front(t_list *list, int to_free)
{
	t_list		*ret;

	if (!list)
		return (NULL);
	ret = list->next;
	if (to_free)
		free(list->content);
	free(list);
	return (ret);
}

t_list			*list_remove_back(t_list *list, int to_free)
{
	t_list		*to_del;
	t_list		*ret;

	if (!list)
		return (NULL);
	if (!list->next)
	{
		if (to_free)
			free(list->content);
		free(list);
		return (NULL);
	}
	ret = list;
	while (list->next && list->next->next)
		list = list->next;
	to_del = list->next;
	if (to_free)
		free(to_del->content);
	free(to_del);
	list->next = NULL;
	return (ret);
}

t_list			*list_add_front(t_list *list, void *content)
{
	t_list		*item;

	if (!list)
		return (list_create(content));
	if (!(item = malloc(sizeof(t_list))))
		ft_error("Malloc error");
	item->content = content;
	item->next = list;
	return (item);
}

t_list			*list_add_back(t_list *list, void *content)
{
	t_list		*item;
	t_list		*ret;

	if (!list)
		return (list_create(content));
	ret = list;
	while (list->next)
		list = list->next;
	if (!(item = malloc(sizeof(t_list))))
		ft_error("Malloc error");
	item->content = content;
	item->next = NULL;
	list->next = item;
	return (ret);
}

t_list			*list_create(void *content)
{
	t_list		*ret;

	if (!(ret = malloc(sizeof(t_list))))
		ft_error("Malloc error");
	ret->content = content;
	ret->next = NULL;
	return (ret);
}
