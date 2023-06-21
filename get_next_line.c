/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:55:22 by julberna          #+#    #+#             */
/*   Updated: 2023/06/20 21:31:51 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *rest, int nb_read);
char	*ft_get_line(char *str);
char	*ft_get_leftover(char *str);
char	*ft_substr(const char *s, unsigned int start, size_t len);

char	*get_next_line(int fd)
{
	int			nb_read;
	char		*line_return;
	char		*str;
	static char	*rest;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nb_read = 1;
	str = ft_read_file(fd, rest, nb_read);
	if (!str)
	{
		free(str);
		rest = NULL;
		return (NULL);
	}
	line_return = ft_get_line(str);
	if (ft_strlen(line_return) == 0)
	{
		free(line_return);
		free(str);
		rest = NULL;
		return (NULL);
	}
	rest = ft_get_leftover(str);
	free(str);
	return (line_return);
}

char	*ft_read_file(int fd, char *rest, int nb_read)
{
	char	*buffer;
	char	*temp_buffer;
	char	*free_temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	temp_buffer = NULL;
	free_temp = NULL;
	if (rest)
		temp_buffer = ft_strjoin(temp_buffer, rest);
	if (rest)
		free(rest);
	while (nb_read)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read <= 0)
			break ;
		free_temp = temp_buffer;
		buffer[nb_read] = '\0';
		temp_buffer = ft_strjoin(temp_buffer, buffer);
		free(free_temp);
		if (ft_strchr(temp_buffer, '\n') || nb_read <= 0)
			break ;
	}
	free(buffer);
	if (nb_read < 0)
	{
		free(temp_buffer);
		return (NULL);
	}
	return (temp_buffer);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		i++;
	}
	line = ft_calloc((i + 2), sizeof(char));
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = '\n';
		line[i + 1] = '\0';
	}
	else
		line[i] = '\0';
	return (line);
}

char	*ft_get_leftover(char *str)
{
	char	*rest;
	int		i;

	if (!str)
		return (NULL);
	rest = NULL;
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	rest = ft_substr(str, i, ft_strlen(&str[i]));
	return (rest);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;

	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		len = 0;
		start = ft_strlen(s);
	}
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substr = ft_calloc((len + 1), sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_strlcat(substr, s + start, len + 1);
	return (substr);
}
