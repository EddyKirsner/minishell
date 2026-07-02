/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 16:26:22 by ktaouach          #+#    #+#             */
/*   Updated: 2025/02/25 19:21:40 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static
	int	check_word(const char *str, unsigned int i)
{
	if ((is_in_quote((char *)str, i) && i) || is_whitespace(str[i]))
		return (0);
	if (i == 0 && !is_whitespace(str[i]))
		return (1);
	if (is_whitespace(str[i - 1]))
		return (1);
	return (0);
}

static
	char	**alloc_segments(const char *str)
{
	char			**tab;
	unsigned int	count;
	unsigned int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (check_word(str, i))
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
	char	*place_word(const char *s, size_t count, char **tab)
{
	char	*str;
	size_t	j;

	j = 0;
	while (s[j] && (!is_whitespace(s[j]) || is_in_quote((char *)s, j)))
		j++;
	str = ft_substr(s, 0, j);
	if (str == NULL)
	{
		free_mem(tab, count);
		return (NULL);
	}
	return (str);
}

char	**ft_split_quotes(char const *s)
{
	unsigned int	i;
	unsigned int	j;
	char			**tab;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	tab = alloc_segments(s);
	while (s[i] && tab != NULL)
	{
		if (check_word(s, i))
		{
			tab[j] = place_word((char *)&s[i], j, tab);
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
