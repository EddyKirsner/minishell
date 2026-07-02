/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 11:21:51 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/28 16:35:19 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static
	char	*fuse(char *overall, char *buffer, ssize_t *restart)
{
	char	*res;
	size_t	i;
	size_t	total;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	total = ft_strlen(overall) + i;
	res = malloc((total + 1) * (sizeof(char)));
	if (!res)
		return (NULL);
	if (overall)
		ft_strlcpy(res, overall, ft_strlen(overall) + 1);
	ft_strlcpy(&res[ft_strlen(overall)], buffer, i + 1);
	ft_strlcpy(buffer, &buffer[i], ft_strlen(&buffer[i]) + 1);
	free(overall);
	if (ft_strchr(res, '\n'))
		*restart = 0;
	return (res);
}

static
	ssize_t	reading(int fd, char *buffer)
{
	ssize_t	res;

	res = read(fd, buffer, BUFFER_SIZE);
	if (res > 0 && BUFFER_SIZE > 1 && res < BUFFER_SIZE)
		buffer[res] = '\0';
	return (res);
}

char	*get_next_line(int fd)
{
	char			*result;
	static char		buffer[1024][BUFFER_SIZE + 1] = {0};
	ssize_t			restart;

	if (fd < 0)
		return (NULL);
	if (!buffer[fd][0])
		ft_bzero(buffer[fd], BUFFER_SIZE + 1);
	result = NULL;
	restart = 1;
	while (restart)
	{
		result = fuse(result, buffer[fd], &restart);
		if (!result)
			return (NULL);
		if (!ft_strchr(result, '\n') && !ft_strchr(buffer[fd], '\n'))
			restart = reading(fd, buffer[fd]);
		if (restart < 0 || (!result[0] && !restart))
			return (free(result), NULL);
	}
	return (result);
}
