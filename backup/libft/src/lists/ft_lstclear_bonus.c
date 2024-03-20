/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 03:09:15 by akambou           #+#    #+#             */
/*   Updated: 2023/11/22 23:22:18 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*end;

	while (*lst)
	{
		end = (*lst)-> next;
		del((*lst)-> content);
		free(*lst);
		(*lst) = end;
	}
}
