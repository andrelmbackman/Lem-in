/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_printf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:00:57 by leo               #+#    #+#             */
/*   Updated: 2022/03/03 23:41:36 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	char_print(t_formats *mod)
{
	unsigned char	c;

	c = (unsigned char)va_arg(mod->args, int);
	while (mod->width - 1 > 0 && (mod->formatcombo & DASH) == 0)
	{
		mod->char_count += write(1, " ", 1);
		mod->width--;
	}
	mod->char_count += write(1, &c, 1);
	while (mod->width-- - 1 > 0)
		mod->char_count += write(1, " ", 1);
}

void	percentage_putchar(t_formats *mod)
{
	mod->width -= 1;
	if ((mod->formatcombo & HPS_ZD) == 0 && mod->width - 1 > 0)
	{
		width_print(mod);
	}	
	if ((mod->formatcombo & ZERO) != 0)
		zero_print(mod);
	mod->char_count += write(1, "%", 1);
	while (mod->width-- > 0 && (mod->formatcombo & DASH) != 0)
		mod->char_count += write(1, " ", 1);
}

void	error_print(t_formats *mod)
{
	mod->char_count += 0;
	return ;
}
