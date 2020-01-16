/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 13:53:32 by wstygg            #+#    #+#             */
/*   Updated: 2019/10/27 13:53:33 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

typedef	struct		s_list
{
	struct s_list	*next;
	void			*content;
}					t_list;

t_list				*list_add_at(t_list *lst, int at, void *content);
t_list				*list_remove_at(t_list *lst, int at, int to_free);
t_list				*list_at(t_list *lst, int at);
t_list				*list_remove_front(t_list *list, int to_free);
t_list				*list_remove_back(t_list *list, int to_free);
t_list				*list_add_front(t_list *list, void *content);
t_list				*list_add_back(t_list *list, void *content);
t_list				*list_create(void *content);
t_list				*list_remove_all(t_list *list, int to_free);
int					list_length(t_list *list);

#endif
