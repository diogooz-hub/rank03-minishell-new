/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:34:14 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/04 00:34:14 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	while (str[i])
		i++;
	while (i >= 0 && str[i] != (char)c)
		i--;
	if (str[i] == (char)c)
	{
		ptr = (char *)str + i;
		return (ptr);
	}
	else
		return (NULL);
}
/*
int main ()
{
    const char str[] = "/Hello /world";
    char c = '/';
    printf("%s", ft_strrchr(str, c));
    return (0);
}
*/
