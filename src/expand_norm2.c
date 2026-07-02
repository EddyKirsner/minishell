/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_norm2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekirsner <ekirsner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 18:57:22 by ekirsner          #+#    #+#             */
/*   Updated: 2025/04/05 15:59:03 by ekirsner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_free_and_return(char *str)
{
	free(str);
	return (NULL);
}

char	*ft_close_and_return(char *str, int i)
{
	str[i] = '\0';
	return (str);
}

int	ft_fail_memory(void)
{
	ft_putstr_fd("memory allocation failed\n", 1);
	return (0);
}

int	ft_count_and_free0(int *full_lenght, char *env_copy)
{
	int	to_free;

	to_free = ft_count_and_free(env_copy);
	if (!to_free)
		return (0);
	*full_lenght += to_free;
	return (1);
}
