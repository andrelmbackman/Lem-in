/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_formats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 18:05:01 by leo               #+#    #+#             */
/*   Updated: 2022/03/03 19:14:05 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*overwrite_zeroflag(char *format, t_formats *mod)
{
	if (mod->uint_flag[0] == ZERO)
		mod->uint_flag[0] = DASH;
	else if (mod->uint_flag[1] == ZERO)
		mod->uint_flag[1] = DASH;
	return (format);
}

char	*get_flag(char *format, t_formats *mod)
{
	int			i;
	int			j;
	char		c;

	i = 0;
	j = 0;
	while (FLAGS[i])
	{
		if (FLAGS[i] == *format && mod->uint_flag[j] == FLAG_NULL && j != 2)
		{
			mod->uint_flag[j] ^= 1 << i;
			mod->flag[j++] = i;
			c = *format;
			while (*format == c)
				format++;
			i = 0;
			continue ;
		}
		i++;
	}
	if (*format == '-')
		overwrite_zeroflag(format++, mod);
	get_formatcombo(mod);
	return (get_width(&(*format), mod, WIDTH));
}

char	*get_width(char *format, t_formats *mod, int flag)
{
	int	i;

	i = 0;
	if (flag == PRECISION)
		format++;
	while (*format == '0')
		format++;
	if (ft_isdigit(*format))
	{
		i = *format++ - '0';
		while (ft_isdigit(*format))
			i = (i * 10) + (*format++ - '0');
		if (flag == PRECISION)
			mod->precision = i;
		else
			mod->width = i;
	}
	mod->uint_flag[2] ^= flag;
	if (*format == '*')
	{
		asterisk_flag(mod, flag);
		format++;
	}	
	return (&(*format));
}

char	*get_length(char *format, t_formats *mod)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (LENGTH[i])
	{
		if (LENGTH[i] == format[j] && mod->length == LENGTH_NULL)
		{
			mod->length = i;
			format++;
			if (format[j] == format[j - 1])
			{
				mod->length = i + 1;
				format++;
			}	
		}
		i++;
	}
	return (&(*format));
}

int	get_specifier(t_formats *mod, char c)
{
	int	i;

	i = 0;
	while (CONVERSION[i])
	{
		if (CONVERSION[i] == c)
		{
			mod->specifier = c;
			g_printf[g_conversion[i]](mod);
			ft_strdel(&mod->num);
			return (1);
		}
		i++;
	}
	return (0);
}
