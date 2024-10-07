/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_single_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 22:45:11 by pedalexa          #+#    #+#             */
/*   Updated: 2024/05/02 17:06:39 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_single_cmd(char *str, char *cmd)
{
	size_t	i;
	size_t	h;

	i = 0;
	h = 0;
	if (ft_strlen(str) < ft_strlen(cmd))
		return (0);
	while (str[i] == ' ')
		i++;
	while (str[i] && cmd[h])
	{
		if (str[i] != cmd[h])
			return (0);
		i++;
		h++;
	}
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
