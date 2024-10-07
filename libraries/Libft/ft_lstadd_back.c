/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 16:32:56 by pedalexa          #+#    #+#             */
/*   Updated: 2023/11/07 11:18:32 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	temp = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (temp -> next != NULL)
	{
		temp = temp -> next;
	}
	temp -> next = new;
}
/*
int main()
{
    t_list *my_list = NULL;
    // Add nodes to the list
    ft_lstadd_back(&my_list, ft_lstnew("Node 1"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 2"));
    ft_lstadd_back(&my_list, ft_lstnew("Node 3"));
    // Print the elements in the list
    t_list *current = my_list;
    while (current)
    {
        printf("%s\n", (char *)current->content);
        current = current->next;
    }
    return 0;
}
*/