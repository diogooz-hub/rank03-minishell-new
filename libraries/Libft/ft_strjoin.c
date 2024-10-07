/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:27:06 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/04 00:27:06 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		h;
	char	*str;

	i = 0;
	h = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[h] != '\0')
	{
		str[i] = s2[h];
		i++;
		h++;
	}
	str[i] = '\0';
	return (str);
}
/*
int main ()
{
    const char s1[] = "Ola ";
    const char s2[] = "eu sou o Pedro\n";

    printf("%s", ft_strjoin(s1, s2));
    return 0;
}
*/
