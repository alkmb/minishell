/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 01:46:56 by akambou           #+#    #+#             */
/*   Updated: 2023/11/22 23:22:00 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*new_node;

	new_node = 0;
	if (lst)
	{
		if (*lst)
		{
			new_node = ft_lstlast(*(lst));
			new_node -> next = new;
		}
		else
			*lst = new;
	}
}
