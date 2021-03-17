/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchevet <jchevet@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 13:23:02 by jchevet           #+#    #+#             */
/*   Updated: 2021/03/03 14:59:06 by jchevet          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_treatment(char **str, int fd, char **line, char *tmp)
{
	int i;

	i = 0;
	while (str[fd][i] != '\n' && str[fd][i] != '\0')
		i++;
	if (str[fd][i] == '\n')
	{
		*line = ft_substr(str[fd], 0, i);
		tmp = str[fd];
		str[fd] = ft_substr(str[fd], i + 1, ft_strlen(str[fd]));
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_strdup(str[fd]);
		free(str[fd]);
		str[fd] = NULL;
		return (0);
	}
}

int		check_errors(int fd, char **line, char **str)
{
	if (read(fd, str[fd], 0) != 0 || line == NULL || BUFFER_SIZE == 0)
	{
		*line = NULL;
		return (0);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*str[10240];
	int			bytes_read;
	char		*tmp;

	if (!check_errors(fd, line, str))
		return (-1);
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[bytes_read] = '\0';
		if (!str[fd])
			str[fd] = ft_strdup(buffer);
		else
		{
			tmp = str[fd];
			str[fd] = ft_strjoin(str[fd], buffer);
			free(tmp);
		}
		if (str[fd] == NULL || ft_strchr(str[fd], '\n'))
			break ;
	}
	if (str[fd] != NULL)
		return (ft_str_treatment(str, fd, line, tmp));
	*line = ft_strdup("");
	return (0);
}

