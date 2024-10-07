/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:32:33 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/04 00:32:33 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *little, size_t len)
{
	size_t	i;
	size_t	h;

	i = 0;
	h = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (big[i] == little[h])
		{
			while (i < len && big[i] == little[h] && big[i] && little[h])
			{
				i++;
				h++;
			}
			if (little[h] == '\0')
				return ((char *)big + i - h);
			i = i - h + 1;
		}
		else
			i++;
		h = 0;
	}
	return (NULL);
}
/*
int main ()
{
    const char big[] = "123456789";
    const char little[] = "9";
    size_t len = 8;

    printf("%s\n", ft_strnstr(big, little, len));
    return (0);
}
*/
