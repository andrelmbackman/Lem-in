/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:44:08 by leotran           #+#    #+#             */
/*   Updated: 2022/03/21 10:38:14 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	get_formatcombo(t_formats *mod)
{
	u_int16_t	flag0;
	u_int16_t	flag1;

	flag0 = mod->uint_flag[0];
	flag1 = mod->uint_flag[1];
	mod->formatcombo = flag0 | flag1;
	return (0);
}

void	reset_t_formats(t_formats *mod, int flag)
{
	mod->uint_flag[0] = FLAG_NULL;
	mod->uint_flag[1] = FLAG_NULL;
	mod->uint_flag[2] = FLAG_NULL;
	mod->flag[0] = ERROR_FLAG;
	mod->flag[1] = ERROR_FLAG;
	mod->length = LENGTH_NULL;
	mod->width = 0;
	mod->precision = 0;
	mod->specifier = 0;
	mod->formatcombo = 0;
	mod->num = NULL;
	if (flag == 1)
		mod->char_count = 0;
}

void	get_signed_type(t_formats *mod)
{
	long long	num;

	num = va_arg(mod->args, long long);
	if (mod->length == H)
		mod->num = ft_itoa((short)num);
	else if (mod->length == HH)
		mod->num = ft_itoa((signed char)num);
	else if (mod->length == L || mod->length == Z)
		mod->num = ft_itoa_base((long)num, 10, 0);
	else if (mod->length == LL)
		mod->num = ft_itoa_base((long long)num, 10, 0);
	else
		mod->num = ft_itoa((int)num);
}

void	get_unsigned_type(t_formats *mod, int base, int flag)
{
	unsigned long long	num;

	num = va_arg(mod->args, unsigned long long);
	if (mod->length == H)
		mod->num = ft_uitoa_base((unsigned short)num, base, flag);
	else if (mod->length == HH)
		mod->num = ft_uitoa_base((unsigned char)num, base, flag);
	else if (mod->length == L || mod->length == Z)
		mod->num = ft_uitoa_base((unsigned long)num, base, flag);
	else if (mod->length == LL)
		mod->num = ft_uitoa_base((unsigned long long)num, base, flag);
	else
		mod->num = ft_uitoa_base((unsigned int)num, base, flag);
}
