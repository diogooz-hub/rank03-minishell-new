/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:38:49 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/14 21:16:40 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!src && !dest)
		return (dest);
	if (src > dest)
		return (ft_memcpy(dest, src, n));
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (n--)
		d[n] = s[n];
	return (dest);
}
/*
int main()
{
	char	str[] = "Vou ser copiado.";
	char	dest[1];
	ft_putstr_fd(ft_memmove(dest, str, 10), 1);
	ft_putchar_fd('\n', 1);
}
*/
