/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:26:22 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/08 14:14:08 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static
	int	check_word(const char *str, char c, unsigned int i)
{
	if (!str[i] || str[i] == c)
		return (0);
	if (i == 0 && str[i] != c)
		return (1);
	if (str[i - 1] == c)
		return (1);
	return (0);
}

static
	char	**alloc_segments(const char *str, char c)
{
	char			**tab;
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (check_word(str, c, i))
			count++;
		i++;
	}
	count++;
	tab = malloc((count) * (sizeof(char *)));
	return (tab);
}

static
	void	free_mem(char **tab, size_t count)
{
	unsigned int	i;

	i = 0;
	while (count > i)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static
	char	*place_word(const char *s, char c, size_t count, char **tab)
{
	char	*str;
	size_t	j;

	j = 0;
	while (s[j] && s[j] != c)
		j++;
	str = ft_substr(s, 0, j);
	if (str == NULL)
	{
		free_mem(tab, count);
		return (NULL);
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	tab = alloc_segments(s, c);
	while (s[i] && tab != NULL)
	{
		if (check_word(s, c, i))
		{
			tab[j] = place_word((char *)&s[i], c, j, tab);
			if (tab[j] == NULL)
				return (NULL);
			j++;
		}
		i++;
	}
	if (tab != NULL)
		tab[j] = NULL;
	return (tab);
}
