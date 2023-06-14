/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 21:55:22 by julberna          #+#    #+#             */
/*   Updated: 2023/06/13 21:55:10 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	ft_allocation(int fd);
char	ft_print(char *temp_buffer);

char	*get_next_line(int fd)
{
	char	*str_return;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return (ft_allocation(fd));
}

char	ft_allocation(int fd)
{
	char		*buffer;
	static char	*temp_buffer;
	int			nb_read;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	buffer[BUFFER_SIZE] = '\0';
	if (!temp_buffer)
	{
		temp_buffer = malloc(1);
	}
	while (!ft_strchr(buffer, '\n'))
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read == 0)
			break ;
		buffer[nb_read] = '\0';
		temp_buffer = ft_strjoin(temp_buffer, buffer);
	}
	free (buffer);
	return (ft_print(temp_buffer));
}

char	ft_print(char *temp_buffer)
{
	char		*line_return;
	size_t		j;

	j = 0;
	line_return = malloc(100 * sizeof(char));
	while (*temp_buffer != '\n')
	{
		ft_putchar_fd(*temp_buffer, 1);
		line_return[j] = temp_buffer[0];
		j++;
		temp_buffer++;
	}
	if (ft_strchr(temp_buffer, '\n'))
	{
		ft_putchar_fd(*temp_buffer, 1);
		temp_buffer++;
	}
	return (*line_return);
}
