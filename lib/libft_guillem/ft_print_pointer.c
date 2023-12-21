/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gprada-t <gprada-t@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 00:13:44 by gprada-t          #+#    #+#             */
/*   Updated: 2023/12/18 10:29:42 by gpradat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_pointer(unsigned long ptr, int *len)
{
	ft_print_str("0x", len);
	if (*len == -1)
		return ;
	if (ptr == 0)
	{
		ft_put_char('0', len);
		if (*len == -1)
			return ;
		return ;
	}
	ft_put_hex(ptr, len);
	if (*len == -1)
		return ;
}
