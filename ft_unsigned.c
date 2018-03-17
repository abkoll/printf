/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 07:16:46 by akoller           #+#    #+#             */
/*   Updated: 2018/03/07 07:16:50 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void			ft_writeoct(t_print *f, uintmax_t i, uintmax_t power)
{
	while (i == 0 && power > 0)
	{
		if (f->precision != 0 || (f->hash == 1 && f->data == VAR_OCT))
		{
			write(1, "0", 1);
			f->done++;
		}
		power = power / f->base;
	}
}

void			ft_printunsignednum(t_print *f, uintmax_t i)
{
	char		c;
	uintmax_t	power;
	int			cap;

	cap = (f->caps) ? '7' : 'W';
	power = ft_upow(f);
	while (i != 0 && power != 0)
	{
		if ((i / power) > 9)
		{
			c = ((i / power) + cap);
			write(1, &c, 1);
			f->done++;
		}
		else
		{
			c = (i / power) + '0';
			write(1, &c, 1);
			f->done++;
		}
		i = i - (i / power) * power;
		power = power / f->base;
	}
	ft_writeoct(f, i, power);
}

void			ft_uprefix(t_print *f, uintmax_t i)
{
	if (f->data == VAR_PTR || ((f->hash == 1 && i != 0) &&
		(f->data == VAR_OCT || f->data == VAR_HEX)))
	{
		write(1, "0", 1);
		f->done++;
		if ((f->data == VAR_HEX && f->caps == 0) || f->data == VAR_PTR)
		{
			write(1, "x", 1);
			f->done++;
		}
		else if (f->data == VAR_HEX && f->caps == 1)
		{
			write(1, "X", 1);
			f->done++;
		}
	}
}

void			ft_putunsigned(t_print *f, uintmax_t i, int zeroes, int spaces)
{
	while (f->minus == 0 && spaces-- > 0)
	{
		write(1, " ", 1);
		f->done++;
	}
	ft_uprefix(f, i);
	while (zeroes-- > 0)
	{
		write(1, "0", 1);
		f->done++;
	}
	ft_printunsignednum(f, i);
	while (f->minus == 1 && (spaces-- > 0))
	{
		write(1, " ", 1);
		f->done++;
	}
}

void			ft_printunsigned(t_print *f, uintmax_t i)
{
	int			zeroes;
	int			spaces;

	f->udigits = ft_udigits(f, i);
	zeroes = ft_unsignedzero(f);
	spaces = f->padding - f->udigits - zeroes;
	if (f->hash == 1 && f->data == VAR_OCT)
		zeroes--;
	if (i == 0 && f->precision == 0)
		spaces++;
	if (f->data == VAR_PTR || (f->hash == 1 && f->data == VAR_HEX))
		spaces -= 2;
	else if (f->hash == 1 && f->data == VAR_OCT)
		spaces--;
	ft_putunsigned(f, i, zeroes, spaces);
}
