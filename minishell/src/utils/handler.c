/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmb <kmb@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:49:13 by kmb               #+#    #+#             */
/*   Updated: 2024/05/05 14:10:52 by kmb              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_repetition(char *input)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (ft_strncmp(input, "\"", 1) == 0 
		|| ft_strncmp(input, "\'", 1) == 0)
	{
		while ((input[i] == '\"' || input[i] == '|') && i < len)
			i++;			
			return (0);
		if (i == len)
			return (0);
	}
	else if (ft_strncmp(input, " ", 1) == 0 
		|| ft_strncmp(input, "\t", 1) == 0
		|| ft_strncmp(input, "|", 1) == 0)
	{
		while (input[i] == ' ' || input[i] == '\t' || input[i] == '|')
			i++;
		if (i == len)
			return (0);
	}
}

int	handle_exception(char *input)
{
	int	i;

	i = 0;
	if (ft_strcmp(input, EXCEPTION) == 0)
	{
		printf(EXCEPTION_R);
		return (0);
	}
	return (1);
}
