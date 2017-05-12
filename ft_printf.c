/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yzakharc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:31:20 by yzakharc          #+#    #+#             */
/*   Updated: 2017/05/10 20:39:58 by yzakharc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		skip_zero(const char **fl, t_pf *pf)
{
	**fl == '0' ? pf->zero = 1 : 0;
	while (**fl == '0' && **fl)
		(*fl)++;
	return (0);
}

int		skip_hh_ll(const char **fl, t_pf *pf)
{
	if (**fl == 'h' && *(*fl + 1) == 'h')
	{
		pf->hh = 1;
		(*fl) += 2;
	}
	if (**fl == 'l' && *(*fl + 1) == 'l')
	{
		pf->ll = 1;
		(*fl) += 2;
	}
	return (0);
}

int		ft_check_fl(const char **fl, t_pf *pf, va_list *fm)
{
	while (ft_strchr(pf->f_l, **fl) && **fl)
	{
		if (**fl == '0')
			return (skip_zero(fl, pf));
		**fl == '#' ? pf->sharp = 1 : 0;
		**fl == '-' ? pf->dash = 1 : 0;
		**fl == '+' ? pf->plus = 1 : 0;
		**fl == ' ' ? pf->space = 1 : 0;
		if (**fl == '.')
			return (check_dot(pf, fl, fm));
		**fl == 'h' && *(*fl + 1) != 'h' ? pf->h = 1 : 0;
		if (**fl == 'h' && *(*fl + 1) == 'h')
			return (skip_hh_ll(fl, pf));
		**fl == 'l' && *(*fl + 1) != 'l' ? pf->l = 1 : 0;
		if (**fl == 'l' && *(*fl + 1) == 'l')
			return (skip_hh_ll(fl, pf));
		**fl == 'j' ? pf->j = 1 : 0;
		**fl == 'z' ? pf->z = 1 : 0;
		if (ft_isdigit(**fl) || **fl == '*')
			return (check_width(pf, fl, fm));
		(*fl)++;
	}
	return (0);
}

int		ft_check_form(const char *form, va_list *fm, t_pf *pf)
{
	while (*form)
	{
		clean_all(pf);
		while (*form != '%' && *form)
		{
			putchar_pf(*form, pf);
			form++;
		}
		*form ? form++ : 0;
		while (ft_strchr(pf->f_l, *form) && *form)
			ft_check_fl(&form, pf, fm);
		*form == 'U' || *form == 'D' || *form == 'O' ? pf->l = 1 : 0;
		ft_trunk(pf);
		if (ft_strchr(pf->s_p, *form) && *form)
			ft_check_sp(*form, fm, pf);
		else
			*form ? ft_check_smb(form, pf) : 0;
		*form ? form++ : 0;
	}
	return (pf->print_smb);
}

int		ft_printf(const char *format, ...)
{
	va_list	fm;
	int		how_mach;
	t_pf	pf;

	pf.s_p = "spdDioOuUxXcCn";
	pf.f_l = "#0-+  .hljz123456789*";
	pf.print_smb = 0;
	va_start(fm, format);
	how_mach = ft_check_form(format, &fm, &pf);
	va_end(fm);
	pf.str_clean == 1 ? ft_strdel(&pf.str) : 0;
	clean_all(&pf);
	return (how_mach);
}
