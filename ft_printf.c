/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akoller <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 12:06:09 by akoller           #+#    #+#             */
/*   Updated: 2018/03/07 22:22:14 by akoller          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftprintf.h"

void		ft_parser(const char *format, t_print *f)
{
	while (format[f->index] != '%' && format[f->index])
	{
		write(1, &format[f->index], 1);
		f->done++;
		f->index++;
	}
	if (format[f->index] == '%')
		f->index++;
		if (format[f->index] == '%')
		{
			write (1, &format[f->index], 1);
			f->index++;
			f->done++;
		 	ft_parser(format, f);
		}
		else ft_escapeparser(format, f);
}

void		ft_write(t_print *f, char c)
{
	write(1, &c, 1);
	f->done++;
}

void		ft_numbase(t_print *f)
{
	f->base = 10;
	if (f->data == VAR_OCT)
		f->base = 8;
	else if (f->data == VAR_HEX || f->data == VAR_PTR)
		f->base = 16;
}

void		ft_varcheck(const char *fm, t_print *f)
{
	if (fm[f->index] == 'c' || fm[f->index] == 'C')
		f->data = VAR_C;
	else if (fm[f->index] == 'd' || fm[f->index] == 'D' || fm[f->index] == 'i')
		f->data = VAR_I;
	else if (fm[f->index] == 's' || fm[f->index] == 'S')
		f->data = VAR_S;
	else if (fm[f->index] == 'o' || fm[f->index] == 'O')
		f->data = VAR_OCT;
	else if (fm[f->index] == 'x' || fm[f->index] == 'X')
		f->data = VAR_HEX;
	else if (fm[f->index] == 'u' || fm[f->index] == 'U')
		f->data = VAR_UI;
	else if (fm[f->index] == 'p')
		f->data = VAR_PTR;
	else if (fm[f->index])
	{
		f->data = VAR_INVSPC;
		f->invalidspec = fm[f->index];
	}
	if (fm[f->index] > 'A' && fm[f->index] < 'Z')
		f->caps = 1;
	ft_numbase(f);
}

void		ft_varsort(t_print *f, va_list *arg)
{
	if (f->data == VAR_C || f->data == VAR_INVSPC)
		ft_printchar(f, arg);
	if (f->data == VAR_S && f->caps == 1)
		ft_printwidestring(f, arg);
	if (f->data == VAR_S && f->caps == 0)
		ft_printstring(f, arg);
	if (f->data == VAR_I)
		ft_printsigned(f, arg);
	if (f->data == VAR_HEX || f->data == VAR_OCT || f->data == VAR_UI ||
		f->data == VAR_PTR)
		// ft_printunsignedmod(f, arg);
		ft_printunsigned(f, arg);
}

int			ft_printf(const char *format, ...)
{
	va_list	arg;
	t_print	flag;

	flag.index = 0;
	flag.done = 0;
	va_start (arg, format);
	while (format[flag.index])
	{
		ft_parser(format, &flag);
		ft_varcheck(format, &flag);
		ft_varsort(&flag, &arg);
		if(format[flag.index])
			flag.index++;
	}
	va_end (arg);
	return (flag.done);
}