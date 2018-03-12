/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 18:30:11 by akoller           #+#    #+#             */
/*   Updated: 2017/10/12 00:55:24 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

int		ft_atoi(const char *str)
{
	int		i;
	int		negative;

	i = 0;
	negative = 1;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		negative = -1;
		str++;
	}
	while (*str && ft_isdigit(*str))
		i = i * 10 + (*str++ - '0');
	return ((int)i * negative);
}
