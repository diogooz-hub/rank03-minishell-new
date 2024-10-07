/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 00:37:53 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/04 00:37:53 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}
/*
int main (void)
{
	printf("%c", ft_toupper('a'));
	printf("%c", ft_toupper('A'));
	printf("%s", ft_toupper(128: '\200'));
	return (0);
}
*/