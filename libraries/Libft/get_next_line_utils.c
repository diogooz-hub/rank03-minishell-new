/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 17:25:05 by pedalexa          #+#    #+#             */
/*   Updated: 2024/03/19 15:43:17 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_endl(char *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return (-1);
	while (line[i])
	{
		if (line[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_bzero_buffer(char *ptr)
{
	size_t	i;
	size_t	h;

	i = 0;
	h = 0;
	while (ptr[i] && ptr[i] != '\n')
	{
		ptr[i] = 0;
		i++;
	}
	if (ptr[i] == '\n')
	{
		ptr[i++] = 0;
	}
	while (ptr[i])
	{
		ptr[h] = ptr[i];
		i++;
		h++;
	}
	while (ptr[h])
	{
		ptr[h] = 0;
		h++;
	}
}

char	*ft_bzero_line(char *ptr, int flag)
{
	size_t	i;

	i = 0;
	if (flag == -1)
		return (NULL);
	if (flag == 1)
		return (ptr);
	while (ptr[i] && ptr[i] != '\n')
	{
		i++;
	}
	if (ptr[i] == '\n')
	{
		i++;
	}
	while (ptr[i])
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
	}
	if (str[i] == '\n')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin_line(char *s1, char *s2)
{
	int		i;
	int		h;
	char	*str;

	i = 0;
	h = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	if (s1)
	{
		while (s1[i] && s1)
		{
			str[i] = s1[i];
			i++;
		}
	}
	while (s2[h] != '\0' && s2[h] != '\n')
		str[i++] = s2[h++];
	if (s2[h] == '\n')
		str[i++] = s2[h];
	str[i] = '\0';
	str = ft_bzero_line(str, 0);
	return (free(s1), str);
}
