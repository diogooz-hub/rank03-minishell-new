/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedalexa <pedalexa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:58:28 by pedalexa          #+#    #+#             */
/*   Updated: 2023/11/07 11:27:50 by pedalexa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	mallocate_words(const char *s, char c,
							char **splitted, int count_words)
{
	int	i;
	int	h;
	int	counter;

	i = 0;
	h = 0;
	counter = 0;
	while (s[i] == c)
		i++;
	while (count_words > 0)
	{
		if ((s[i] == c && s[i + 1] != c) || !s[i])
		{
			splitted[h] = (char *)malloc((counter + 1) * sizeof(char));
			count_words--;
			h++;
			counter = 0;
		}
		else if (s[i] != c && s[i])
			counter++;
		i++;
	}
}

static void	copy_string(const char *s, char c, char **splitted)
{
	int	i;
	int	h;
	int	j;

	i = 0;
	j = 0;
	h = 0;
	s = (char *)s;
	while (s[i] == c)
		i++;
	while (splitted[j] != (NULL))
	{
		if ((s[i] == c && s[i + 1] != c && s[i + 1]) || !s[i])
		{
			splitted[j][h] = '\0';
			j++;
			h = 0;
		}
		else if (s[i] != c)
		{
			splitted[j][h] = s[i];
			h++;
		}
		i++;
	}
}

static int	count_split(char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			n++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (n);
}

char	**ft_split(char const *s, char c)
{
	int		count_words;
	char	**splitted;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	count_words = count_split((char *)s, c);
	splitted = (char **)malloc((count_words + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	splitted[count_words] = NULL;
	mallocate_words(s, c, splitted, count_words);
	while (i < count_words)
	{
		if (!splitted[i])
			return (NULL);
		i++;
	}
	copy_string(s, c, splitted);
	return (splitted);
}
/*
int main ()
{
	char const s[] = "Ola, eu sou o Pedro.";
	char c = ' ';
	char **splitted = ft_split(s, c);
	int i = 0;
	while (splitted[i])
	{
		printf("%i palavra: %s\n", i, splitted[i]);
		free (splitted[i]);
		i++;
	}
	free (splitted);
	return (0);
}
*/
