/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:45:26 by leotran           #+#    #+#             */
/*   Updated: 2022/09/23 10:38:34 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	get_format_lengths(t_formats *mod)
{
	int	len;
	int	i;
	int	sign;

	len = (int)ft_strlen(mod->num) - (*mod->num == '-');
	i = ((mod->formatcombo & HASH) != 0 && mod->specifier == 'o');
	sign = (mod->precision == 0 && mod->uint_flag[2] == PRECISION);
	if (mod->precision > 0)
		mod->precision -= (len + i);
	if ((mod->formatcombo & DASH_HSP) != 0 || (*mod->num == '-'))
		len += 1 + \
		((mod->formatcombo & HASH) != 0 && mod->specifier != 'o');
	if (*mod->num == '0' && sign == 1)
	{
		*mod->num = '\0';
		len--;
	}
	if (mod->width > 0)
		mod->width -= (len + (mod->precision * (mod->precision > 0)));
}

void	get_float_format_lengths(t_formats *mod)
{
	int	len;
	int	sign;

	len = (int)ft_strlen(mod->num) - (*mod->num == '-');
	sign = (mod->precision == 0 && mod->uint_flag[2] == PRECISION);
	if (*mod->num == '-' || (mod->formatcombo & (PLUS | SPACE)) != 0)
		len++;
	if ((mod->formatcombo & HASH) != 0 && sign == 1)
		len++;
	mod->width -= len;
}

void	width_print(t_formats *mod)
{
	while (mod->width-- > 0)
		mod->char_count += write(1, " ", 1);
}

void	precision_print(t_formats *mod)
{
	while (mod->precision-- > 0)
		mod->char_count += write(1, "0", 1);
}
