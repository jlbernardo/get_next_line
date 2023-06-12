/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julberna <julberna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 22:51:41 by julberna          #+#    #+#             */
/*   Updated: 2023/06/11 20:58:58 by julberna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line_return;
	static int		i;
	int				j;
	ssize_t			nb_read;
	static char		*temp_buffer;

	j = 0;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	buffer[BUFFER_SIZE] = '\0';
	if (!temp_buffer)
		temp_buffer = malloc(1);
	line_return = malloc(100 * sizeof(char));
	if (fd)
	{
		if (temp_buffer[i] == '\n')
			i++;
		while (temp_buffer[i] != '\0' && temp_buffer[i] != '\n')
		{
			nb_read = read(fd, buffer, BUFFER_SIZE);
			buffer[nb_read] = '\0';
			temp_buffer = ft_strjoin(temp_buffer, buffer);
			ft_putchar_fd(temp_buffer[i], 1);
			line_return[j] = temp_buffer[i];
			i++;
			j++;
		}
		if (temp_buffer[i] == '\n' || temp_buffer[i] == '\0')
			ft_putchar_fd(temp_buffer[i], 1);
	}
	else
		return (NULL);
	return (line_return);
}
