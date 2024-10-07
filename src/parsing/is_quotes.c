#include "../../includes/minishell.h"

int	is_quotes(char *str)
{
	size_t	i;
	int		quotes;

	i = 0;
	quotes = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			quotes++;
		i++;
	}
	return (quotes);
}