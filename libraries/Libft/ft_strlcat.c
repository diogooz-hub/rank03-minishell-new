/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:29:07 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/04 00:29:07 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	h;

	i = 0;
	h = 0;
	while (dst[i] && i < size)
		i++;
	while (src[h] && (i + h + 1) < size)
	{
		dst[i + h] = src[h];
		h++;
	}
	if (i < size)
		dst[i + h] = '\0';
	while (src[h])
		h++;
	return (i + h);
}
/*
int main ()
{
    char dst[100] = "hello ";
    const char src[] = "world";
    size_t size = 3;

    printf("%d\n", (int)ft_strlcat(dst, src, size));
    return (0);
}
*/
