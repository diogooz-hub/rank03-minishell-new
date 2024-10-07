/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:34:50 by pedalexa          #+#    #+#             */
/*   Updated: 2023/10/26 15:11:01 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)str;
	while (ptr[i] != '\0' && ptr[i] != (char)c)
	{
		i++;
	}
	if (ptr[i] == (char)c)
		return (&ptr[i]);
	return (NULL);
}
/*
int main ()
{
    const char str[] = "there is so \0m";
    char c = '\0';
    printf("%s", ft_strchr(str, c));
    return (0);
}
*/
