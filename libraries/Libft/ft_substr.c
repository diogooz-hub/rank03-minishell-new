/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:35:35 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/04 00:35:35 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen (s);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > s_len)
		len = s_len - start;
	ptr = (char *)malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[start] != '\0' && len > 0)
	{
		ptr[i] = s[start];
		start++;
		i++;
		len--;
	}
	ptr[i] = '\0';
	return (ptr);
}
