/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akambou <akambou@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:49:13 by kmb               #+#    #+#             */
/*   Updated: 2024/04/17 00:58:30 by akambou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_exception(char *input)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(input);
	if (ft_strcmp(input, EXCEPTION) == 0)
	{
		printf(EXCEPTION_R);
		return (0);
	}
	else if (ft_strncmp(input, " ", 1) == 0)
	{
		while (input[i] == ' ')
			i++;
		if (i == len)
			return (0);
	}
	else if (ft_strncmp(input, "|", 1) == 0)
	{
		while (input[i] == '|')
			i++;
		if (i == len)
			return (0);
	}
	return (1);
}
