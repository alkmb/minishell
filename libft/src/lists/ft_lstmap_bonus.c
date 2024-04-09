/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:59:52 by akambou           #+#    #+#             */
/*   Updated: 2023/11/22 23:22:35 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*content;
	t_list	*first;
	t_list	*new;

	first = NULL;
	while (lst)
	{
		content = f(lst -> content);
		new = ft_lstnew(content);
		if (!new)
		{
			free(content);
			ft_lstclear(&first, del);
			return (NULL);
		}
		ft_lstadd_back(&first, new);
		lst = lst -> next;
	}
	return (first);
}
