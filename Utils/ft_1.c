/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wstygg <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 17:25:58 by wstygg            #+#    #+#             */
/*   Updated: 2020/01/19 17:25:59 by wstygg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/util.h"

int						ft_atoi(const char *str)
{
	size_t				i;
	unsigned long long	result;
	int					sign;

	result = 0;
	i = 0;
	while (!(sign = 0) && str[i] >= 9 && str[i] <= 13)
		i++;
	if (str[i] < '0' || str[i] > '9')
	{
		if (str[i] == '-')
			sign = 1;
		else if (str[i] != '+')
			return (0);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > 9223372036854775807)
			return (sign == 1 ? 0 : -1);
		result = (result * 10) + (str[i++] - '0');
	}
	if (str[i])
		return (-1);
	return (sign == 1 ? -result : result);
}

int						ft_strlen(const char *src)
{
	int					i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

void					ft_putstr(char const *str, int new_str)
{
	if (!str)
		return ;
	write(1, str, ft_strlen(str));
	if (new_str)
		write(1, "\n", 1);
}

int						ft_strcmp(const char *s11, const char *s22)
{
	unsigned int		i;
	unsigned char		*s1;
	unsigned char		*s2;

	s1 = (unsigned char*)s11;
	s2 = (unsigned char*)s22;
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if ((s1[i] == '\0' && s2[i] != '\0') || (s1[i] != '\0' && s2[i] == '\0'))
		return (s1[i] - s2[i]);
	return (0);
}

void					ft_error(const char *error)
{
	ft_putstr("\033[31m", 0);
	ft_putstr(error, 0);
	ft_putstr("\033[0m", 1);
	exit(1);
}
