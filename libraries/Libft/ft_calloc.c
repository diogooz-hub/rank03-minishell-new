/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:19:50 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/03 22:19:50 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(n * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	else
	{
		ft_bzero(ptr, n * size);
		return (ptr);
	}
}
