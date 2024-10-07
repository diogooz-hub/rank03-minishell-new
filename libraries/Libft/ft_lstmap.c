/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:47:22 by pedalexa          #+#    #+#             */
/*   Updated: 2023/11/07 11:13:49 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp;

	new = NULL;
	while (lst)
	{
		temp = ft_lstnew((*f)(lst->content));
		if (temp == NULL)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}
		ft_lstadd_back(&new, temp);
		lst = lst -> next;
	}
	return (new);
}
/*
// Function to convert a string to uppercase
void *string_to_uppercase(void *data)
{
    char *str = (char *)data;
    char *new_str = ft_strdup(str);
    if (new_str)
    {
        int i = 0;
        while (new_str[i])
        {
            new_str[i] = ft_toupper(new_str[i]);
            i++;
        }
    }
    return new_str;
}
int main(void)
{
    // Create a linked list with three strings
    t_list *lst = ft_lstnew("hello");
    ft_lstadd_back(&lst, ft_lstnew("world"));
    ft_lstadd_back(&lst, ft_lstnew("libft"));
    // Apply the ft_lstmap function to convert strings to uppercase
    t_list *uppercase_list = ft_lstmap(lst, string_to_uppercase, free);
    t_list *temp;
    // Print the mapped list (uppercase strings)
    printf("Uppercase list:\n");
    temp = uppercase_list;
    while (temp)
    {
        printf("%s -> ", (char *)(temp->content));
        temp = temp->next;
    }
    printf("NULL\n");
    return (0);
}
*/
