#include "../Includes/Utils.h"

void			ft_free(char **to_free)
{
	free(*to_free);
	*to_free = NULL;
}

char			*ft_strsub(char const *s, int start, size_t len)
{
	char		*str;
	size_t		j;

	if (!s || start > ft_strlen(s))
		return (NULL);
	if (!(str = (char *)malloc(len + 1)))
		ft_error("Malloc error");
	j = 0;
	while (s[start] && j < len)
		str[j++] = s[start++];
	str[j] = '\0';
	return (str);
}

char			*ft_strdup(const char *s1)
{
	char		*str;
	size_t		i;

	if (!(str = (char*)malloc(ft_strlen((char*)s1) + 1)))
		ft_error("Malloc error");
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int				ft_str_fd(char **str, char **line, int fd, int res)
{
	int			i;
	char		*src;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (!str[fd][i])
	{
		if (res == BUFF_SIZE)
			return (get_nl(fd, line));
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
	}
	else if (str[fd][i] == '\n')
	{
		*line = ft_strsub(str[fd], 0, i);
		src = ft_strdup(str[fd] + i + 1);
		free(str[fd]);
		if ((str[fd] = src) && str[fd][0] == '\0')
			ft_free(&str[fd]);
	}
	return (1);
}

int				get_nl(int const fd, char **line)
{
	static char	*str[12288];
	char		*src;
	char		buff[BUFF_SIZE + 1];
	int			bytes;

	if (fd < 0 || fd > 12288 || line == NULL || (read(fd, NULL, 0) < 0))
		return (-1);
	while ((str[fd] ? (!ft_strchr(str[fd], '\n')) : (1)) &&
		   (bytes = read(fd, buff, BUFF_SIZE)))
	{
		buff[bytes] = '\0';
		if (!str[fd])
		{
			malloc_utill((void*)&str[fd], 1);
			str[fd][0] = '\0';
		}
		src = ft_strjoin(str[fd], buff, 1);
		str[fd] = src;
	}
	if (bytes < 0)
		return (-1);
	else if (!bytes && (!str[fd] || !str[fd][0]))
		return (0);
	return (ft_str_fd(str, line, fd, bytes));
}