/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_escparse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 14:37:55 by akoller           #+#    #+#             */
/*   Updated: 2018/03/06 14:38:00 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void	ft_flagset(t_print *f)
{
	f->len = 0;
	f->minus = 0;
	f->plus = 0;
	f->data = 9;
	f->space = 0;
	f->hash = 0;
	f->zero = 0;
	f->precision = -1;
	f->padding = 0;
	f->caps = 0;
	f->digits = 0;
}

void	ft_precision(const char *fm, t_print *f)
{
	if (ft_isdigit(fm[f->index]))
		f->padding = ft_atoi(&fm[f->index]);
	while (ft_isdigit(fm[f->index]))
		f->index++;
	if (fm[f->index] == '.')
	{
		f->index++;
		f->precision = 0;
		f->precision = ft_atoi(&fm[f->index]);
	}
	while (ft_isdigit(fm[f->index]))
		f->index++;
}

// void	ft_sizeflag(const char *fm, t_print *f)
// {
// 	while (fm[f->index] == 'h' || fm[f->index] == 'l' || fm[f->index] == 'j'
// 		|| fm[f->index] == 'z')
// 	{
// 		if ((fm[f->index] == 'h') && (fm[f->index++] == 'h') && (f->len < 1))
// 		{
// 			f->len = PRINTF_HH;
// 			f->index++;
// 		}
// 		else if ((fm[f->index] == 'h') && (fm[f->index++] != 'h') && 
// 			(f->len < PRINTF_H))
// 			f->len = PRINTF_H;
// 		else if ((fm[f->index] == 'l') && (fm[f->index++] == 'l') && 
// 			f->len < PRINTF_LL)
// 		{
// 			f->len = PRINTF_LL;
// 			f->index++;
// 		}
// 		else if ((fm[f->index] == 'l') && (fm[f->index++] != 'l') &&
// 			f->len < PRINTF_L)
// 			f->len = PRINTF_L;
// 		else if ((fm[f->index] == 'j') && f->len < PRINTF_J)
// 			f->len = PRINTF_J;
// 		else if ((fm[f->index] == 'z') && f->len < PRINTF_Z)
// 			f->len = PRINTF_Z;
// 		f->index++;
// 	}
// 	printf("test");
// 	printf("%d\n", f->len);
// }

void		ft_sizeflag(const char *fm, t_print *f)
{
	while (fm[f->index] == 'h' || fm[f->index] == 'l' ||
			fm[f->index] == 'j' || fm[f->index] == 'z')
	{
		if (fm[f->index] == 'h' && fm[f->index + 1] == 'h')
		{
			f->len = PRINTF_HH;
			f->index++;
		}
		else if (fm[f->index] == 'h' && fm[f->index + 1] != 'h')
			f->len = PRINTF_H;
		else if (fm[f->index] == 'l' && fm[f->index + 1] == 'l')
		{
			f->len = PRINTF_LL;
			f->len++;
		}
		else if (fm[f->index] == 'l' && fm[f->index + 1] != 'l')
			f->len = PRINTF_L;
		else if (fm[f->index] == 'j')
			f->len = PRINTF_J;
		else if (fm[f->index] == 'z')
			f->len = PRINTF_Z;
		f->index++;
	}
}

void	ft_escapeparser(const char *fm, t_print *f)
{
	ft_flagset(f);
	while ((fm[f->index] == '-') || (fm[f->index] == '+') || 
			(fm[f->index] == ' ') || (fm[f->index] == '#') 
			|| (fm[f->index] == '0'))
	{
		if (fm[f->index] == '-')
			f->minus = 1;
		else if (fm[f->index] == '+')
			f->plus = 1;
		else if (fm[f->index] == ' ')
			f->space = 1;
		else if (fm[f->index] == '#')
			f->hash = 1;
		else if (fm[f->index] == '0')
			f->zero = 1;
		f->index++;
	}
	ft_precision(fm, f);
	f->len = PRINTF_NONE;
	ft_sizeflag(fm, f);
}