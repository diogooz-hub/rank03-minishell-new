/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 18:04:44 by pedalexa          #+#    #+#             */
/*   Updated: 2023/11/07 11:16:01 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0')
	{
		ptr[i] = (*f)(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*
char custom_function(unsigned int index, char c)
{
    if (index % 2 != 0) {
        if (c >= 'a' && c <= 'z') {
            return c - 32; // Convert to uppercase
        }
    }
    return c; // Return the character as is
}
int main()
{
    char input_string[] = "hello, World!";
    char *result = ft_strmapi(input_string, &custom_function);
    if (result) {
        printf("Original String: %s\n", input_string);
        printf("Modified String: %s\n", result);
        // Don't forget to free the dynamically allocated memory.
        free(result);
    } else {
        printf("Memory allocation failed.\n");
    }
    return 0;
}
*/