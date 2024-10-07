/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:36:06 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/03 22:36:06 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *string)
{
	char	*dup;
	int		i;

	i = 0;
	dup = (char *)malloc((ft_strlen(string) + 1) * sizeof(char));
	if (dup == NULL)
	{
		return (NULL);
	}
	while (string[i] != '\0')
	{
		dup[i] = string[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
/*
int main ()
{
    const char *str = "Ola eu sou o Pedro";
    char *dup;

    dup = ft_strdup(str);
    printf("%s", dup);
    return (0);
}
*/
