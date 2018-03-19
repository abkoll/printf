/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_charput.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 11:19:02 by akoller           #+#    #+#             */
/*   Updated: 2018/03/19 11:19:18 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

wint_t			ft_chartypecast(t_print *f, wint_t c)
{
	if (f->len == PRINTF_L)
		return (c);
	else
		return ((char)c);
}

void			ft_writechar(t_print *f, wint_t c, char prec)
{
	if (f->minus)
	{
		write(1, &c, 1);
		f->done++;
	}
	while (f->padding-- > 1)
	{
		write(1, &prec, 1);
		f->done++;
	}
	if (f->minus == 0)
	{
		write(1, &c, 1);
		f->done++;
	}
}

void			ft_printchar(t_print *f, va_list *arg)
{
	wint_t		c;
	char		prec;

	prec = (f->data == VAR_INVSPC && f->zero == 1) ? '0' : ' ';
	if (f->data == VAR_C)
	{
		c = va_arg(*(arg), int);
		c = ft_chartypecast(f, c);
	}
	else
		c = f->invalidspec;
	ft_writechar(f, c, prec);
}
