/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:20:45 by pedalexa          #+#    #+#             */
/*   Updated: 2023/10/11 14:43:03 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*nexttemp;

	current = *lst;
	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	while (current != NULL)
	{
		nexttemp = current -> next;
		del(current -> content);
		free(current);
		current = nexttemp;
	}
	*lst = NULL;
}
