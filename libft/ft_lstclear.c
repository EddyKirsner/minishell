/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:33:41 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/03 16:05:02 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*current_alt;

	if (!lst || !del)
		return ;
	current = *lst;
	current_alt = current;
	while (current_alt)
	{
		current = current_alt;
		current_alt = current->next;
		(*del)(current->content);
		free(current);
	}
	*lst = NULL;
}
