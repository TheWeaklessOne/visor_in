/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 19:24:18 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 19:24:19 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISOR_IN_UTIL_H
# define VISOR_IN_UTIL_H

# define BUFF_SIZE	1

# include "list.h"
# include <stdlib.h>
# include <unistd.h>

void				ft_error(const char *str);

int					ft_strcmp(const char *s11, const char *s22);
int					ft_strlen(const char *src);
void				ft_putstr(char const *str, int new_str);
char				**ft_strsplit(const char *str, char c);
int					ft_atoi(const char *str);
char				*ft_strchr(const char *s, int c);
int					get_nl(int const fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2, int to_free);
int					malloc_utill(void **var, unsigned long size);

#endif
