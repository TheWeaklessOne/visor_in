/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 17:48:12 by wstygg            #+#    #+#             */
/*   Updated: 2019/11/05 17:48:13 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/util.h"

int				list_length(t_list *lst)
{
	int			ret;

	ret = 0;
	while (lst)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}

t_list			*list_remove_all(t_list *lst, int to_free)
{
	t_list		*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (to_free)
			free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

t_list			*list_add_at(t_list *lst, int at, void *content)
{
	t_list		*new;
	t_list		*lst_at;
	t_list		*lst_before;

	if (!(lst_at = list_at(lst, at)))
		return (NULL);
	if (lst_at == lst && at != 1)
		return (lst);
	new = list_create(content);
	if (at == 1)
	{
		new->next = lst;
		return (new);
	}
	else
	{
		lst_before = list_at(lst, at - 1);
		new->next = lst_at;
		lst_before->next = new;
	}
	return (lst);
}

t_list			*list_remove_at(t_list *lst, int at, int to_free)
{
	t_list		*lst_at;
	t_list		*lst_before;

	if (!(lst_at = list_at(lst, at)))
		return (NULL);
	if (lst_at == lst && at != 1)
		return (lst);
	if (at == 1)
	{
		lst_before = lst;
		lst = lst->next;
		if (to_free)
			free(lst_before->content);
		free(lst_before);
	}
	else
	{
		lst_before = list_at(lst, at - 1);
		lst_before->next = lst_at->next;
		if (to_free)
			free(lst_at->content);
		free(lst_at);
	}
	return (lst);
}

t_list			*list_at(t_list *lst, int at)
{
	t_list		*ret;
	int			i;

	if (!lst)
		return (NULL);
	if (at <= 0)
		return (lst);
	ret = lst;
	i = 1;
	while (lst->next && i < at)
	{
		lst = lst->next;
		i++;
	}
	if (i == at)
		return (lst);
	return (ret);
}
