/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktaouach <ktaouach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:53:26 by ktaouach          #+#    #+#             */
/*   Updated: 2024/06/28 14:12:35 by ktaouach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*elem;
	void	*cont;

	if (!lst || !f || !del)
		return (NULL);
	cont = f(lst->content);
	new = ft_lstnew(cont);
	if (!new)
		return (free(cont), NULL);
	lst = lst->next;
	while (lst)
	{
		cont = f(lst->content);
		elem = ft_lstnew(cont);
		if (!elem)
			return (del(cont), ft_lstclear(&new, del), NULL);
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
