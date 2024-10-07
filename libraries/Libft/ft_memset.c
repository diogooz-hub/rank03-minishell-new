/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 22:33:53 by pedalexa          #+#    #+#             */
/*   Updated: 2023/09/03 22:33:53 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		((unsigned char *)ptr)[i] = value;
		i++;
	}
	return (ptr);
}
/*
int main(void)
{
    int array[5] = {1, 2, 3, 4, 5};
    char str[] = "Hello, World!";

    // Test with an integer array
    printf("Before memset:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    ft_memset(array, 0, sizeof(int) * 3);

    printf("After memset:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Test with a string
    printf("Before memset: %s\n", str);
    ft_memset(str, '*', 5);
    printf("After memset: %s\n", str);

    return 0;
}
*/
