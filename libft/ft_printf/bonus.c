/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 14:52:08 by leotran           #+#    #+#             */
/*   Updated: 2022/09/23 11:52:52 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	binary_printf(t_formats *mod)
{
	long long	num;

	num = va_arg(mod->args, long long);
	mod->num = ft_itoa_base(num, 2, 0);
	mod->char_count += write(1, mod->num, ft_strlen(mod->num));
}

void	asterisk_flag(t_formats *mod, int flag)
{
	int	num;
	int	sign;

	num = va_arg(mod->args, int);
	sign = 1 - 2 * (num < 0);
	if (sign == -1 && flag == WIDTH)
	{
		if (mod->uint_flag[0] == ZERO || mod->uint_flag[0] == FLAG_NULL)
			mod->uint_flag[0] = DASH;
		else if (mod->uint_flag[1] == ZERO || mod->uint_flag[0] == FLAG_NULL)
			mod->uint_flag[1] = DASH;
	}
	if (flag == WIDTH)
		mod->width = num * sign;
	else
	{
		mod->precision = num * (sign == 1);
		mod->uint_flag[2] = PRECISION * (sign == 1);
	}
	get_formatcombo(mod);
}

void	n_conversion_printf(t_formats *mod)
{
	int	*num;

	num = (int *)va_arg(mod->args, void *);
	*num = mod->char_count;
}

char	*color_printf(char *format)
{
	char	temp[4];
	char	colorcode[8];
	int		i;

	i = 0;
	ft_bzero(temp, 4);
	ft_strcpy(colorcode, "\033[0;3#m");
	ft_strncpy(temp, &format[1], 3);
	while (i < 9 && format[4] == '}')
	{
		if (ft_strcmp(temp, g_colors[i]) == 0)
			break ;
		i++;
	}
	if (i >= 9 || format[4] != '}')
		return (format);
	else if (i == 8)
		write(1, EOC, 4);
	else
	{
		colorcode[5] = i + '0';
		write(1, colorcode, 7);
	}
	return (&format[5]);
}
