/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpaco <dpaco@student.42lisboa.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 09:14:49 by dpaco             #+#    #+#             */
/*   Updated: 2024/10/13 17:40:58 by dpaco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(cmd_list	**cmd)
{
	int 	i;
	char 	**s_array;

	s_array	= (*cmd)->content;
	i = 0;
	if (!strcmp(s_array[1], "-n"))
		i = 2;
	else
		i = 1;
	if (!s_array[i])
	{
		printf("\n");
		return ;
	}
	while (s_array[i])
	{
		//if (!s_array[i + 1])
			printf("%s", s_array[i]);
		//else
		//	printf("%s ", s_array[i]);
		i++;
	}
	if (strcmp(s_array[1], "-n"))
		printf("\n");
}
