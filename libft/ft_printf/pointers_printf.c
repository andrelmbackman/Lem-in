/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointers_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:00:57 by leo               #+#    #+#             */
/*   Updated: 2022/03/09 13:04:43 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	str_print(t_formats *mod)
{
	char	*str;
	int		len;
	int		checker;
	int		i;

	i = 0;
	str = va_arg(mod->args, char *);
	checker = (mod->precision == 0 && mod->uint_flag[2] == PRECISION);
	if (str == NULL)
		str = "(null)";
	len = (int)ft_strlen(str) * (checker == 0);
	if (mod->precision < len && mod->uint_flag[2] == 1 && len > 0)
		len = mod->precision;
	while (mod->width - len > 0 && (mod->formatcombo & DASH) == 0)
	{
		mod->char_count += write(1, " ", 1);
		mod->width--;
	}
	while (*str && i++ < len)
		mod->char_count += write(1, &(*str++), 1);
	while (mod->width-- - len > 0)
		mod->char_count += write(1, " ", 1);
}

void	memaddr_print(t_formats *mod)
{
	unsigned long long	num;
	int					len;

	num = va_arg(mod->args, unsigned long long);
	mod->num = ft_uitoa_base(num, 16, 0);
	len = (int)ft_strlen(mod->num) + 2;
	if (mod->width < len)
		mod->width = 0;
	mod->width -= len * (mod->width > len);
	if ((mod->formatcombo & DASH) == 0 && mod->width > 0)
		width_print(mod);
	mod->char_count += write(1, "0x", 2);
	custom_putstr(mod);
}

void	custom_putstr(t_formats *mod)
{
	int	i;
	int	sign;
	int	precision_check;

	i = 0;
	sign = (((mod->formatcombo ^ DASH) & DASH_HSP) != 0);
	precision_check = (mod->precision == 0 && mod->uint_flag[2] == PRECISION);
	if (precision_check == 1 && *mod->num == '0' \
		&& mod->specifier != 'f' && mod->specifier != 'o')
		*mod->num = '\0';
	if (*mod->num == '-')
		i++;
	while (mod->num[i])
		mod->char_count += write(1, &mod->num[i++], 1);
	if ((mod->formatcombo & HASH) != 0 && precision_check == PRECISION \
		&& mod->specifier == 'f')
		mod->char_count += write(1, ".", 1);
	if (sign == 1 || (mod->formatcombo & DASH) != 0)
		width_print(mod);
}
