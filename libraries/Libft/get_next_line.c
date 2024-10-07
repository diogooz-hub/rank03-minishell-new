/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 00:12:43 by pedalexa          #+#    #+#             */
/*   Updated: 2024/03/19 15:43:08 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	int			bytes_read;
	char		*line;
	int			flag;

	line = NULL;
	flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		if (buffer[0] == '\0')
		{
			bytes_read = read(fd, buffer, BUFFER_SIZE);
			if (bytes_read == 0)
				return (line);
			if (bytes_read < 0)
				return (free(line), NULL);
		}
		line = ft_strjoin_line(line, buffer);
		ft_bzero_buffer(buffer);
		flag = check_endl(line);
		if (flag != 0)
			return (ft_bzero_line(line, flag));
	}
}
/*
int main (void)
{
	char	*filename = "file.txt";
	int	fd;
	char	*line;
	int	count;

	count = 1;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	// line = get_next_line(fd);
	// printf("linha 1: %s", line);
	// line = get_next_line(fd);
	// printf("linha 2: %s", line);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("[%d]: %s\n",count, line);
		free(line);
		count++;
	}
	close(fd);
	return (0);
}
*/