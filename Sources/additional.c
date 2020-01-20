/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:34:58 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 18:35:01 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/visor_in.h"

double			calc_angle(SDL_Point p1, SDL_Point p2)
{
	double		ret;

	if (p1.x == p2.x && p1.y == p2.y)
		return (0);
	ret = SDL_acos((double)((p2.x - p1.x) * p1.x) / p1.x /
			SDL_sqrt(SDL_pow(p2.x - p1.x, 2) +
			SDL_pow(p2.y - p1.y, 2))) * 180 / M_PI;
	return (p1.y < p2.y ? ret : -ret);
}

int				gnl(int fd, char **str)
{
	int		ret;

	if ((ret = get_nl(fd, str)) == -1 || !*str)
		ft_error("Input error");
	return (ret);
}
