/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:57:01 by leo               #+#    #+#             */
/*   Updated: 2022/08/13 11:34:02 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	zero_print(t_formats *mod)
{
	char	c;

	c = '0';
	if (mod->uint_flag[1] == PLUS)
		plus_print(mod);
	if ((mod->formatcombo & DASH) != 0)
		return ;
	if (mod->uint_flag[2] == PRECISION && mod->specifier != 'f')
	{
		c = ' ';
	}	
	while (mod->width-- > 0)
		mod->char_count += write(1, &c, 1);
}

void	hash_print(t_formats *mod)
{
	int	sign;
	int	check_num;

	check_num = (*mod->num == '0' || *mod->num == '\0');
	sign = (mod->specifier == 'X') + (mod->specifier == 'x');
	if ((sign == 1 && check_num != 1) || \
	(*mod->num != '0' && mod->specifier == 'o'))
	{	
		mod->char_count += write(1, "0", 1);
		if (mod->specifier != 'o' && check_num != 1)
			mod->char_count += write(1, &mod->specifier, 1);
	}
	if (mod->uint_flag[1] == ZERO && (mod->uint_flag[2] != PRECISION \
		|| mod->specifier == 'f'))
		zero_print(mod);
}

void	space_print(t_formats *mod)
{
	if (*mod->num != '-' && mod->specifier != 'u' \
		&& (mod->formatcombo & PLUS) == 0)
		mod->char_count += write(1, " ", 1);
	if (mod->uint_flag[1] == ZERO)
		zero_print(mod);
	if (mod->uint_flag[1] == PLUS)
		plus_print(mod);
}

void	dash_print(t_formats *mod)
{
	if ((mod->formatcombo & DASH_HSP) != 0)
		g_flagprint[mod->flag[1]](mod);
}

void	plus_print(t_formats *mod)
{
	if (mod->specifier != 'd' && mod->specifier != 'i' && mod->specifier != 'f')
		return ;
	if (*mod->num != '-')
		mod->char_count += write(1, "+", 1);
	if (mod->uint_flag[1] == ZERO)
		zero_print(mod);
}
