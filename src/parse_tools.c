/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 17:30:27 by abackman          #+#    #+#             */
/*   Updated: 2022/11/29 14:44:42 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* 
** Customised for bonus utility to grep lines required
*/

static void	custom_strcat(char *dst, const char *src, int len, int *lines_req)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[len++] = src[i++];
		if (src[0] == '#' && i == 37 && src[i] == ':')
			*lines_req = ft_atoi(&src[i + 1]);
	}
}

static int	append_line(char **line, t_lemdata **data, int ret)
{
	size_t	tmplen;
	size_t	linelen;
	char	*tmp;

	tmplen = ft_strlen((*data)->antbuf);
	linelen = ft_strlen(*line);
	tmp = ft_strnew(tmplen + linelen + 1);
	if (!tmp)
		memdel_error_exit(data, (void **)line, "Malloc failure");
	ft_strcpy(tmp, (*data)->antbuf);
	custom_strcat(tmp, *line, tmplen, &(*data)->lines_req);
	tmp[tmplen + linelen] = '\n';
	ft_strdel(&(*data)->antbuf);
	(*data)->antbuf = tmp;
	return (ret);
}

int	save_next_line(char **line, t_lemdata **data)
{
	int		ret;

	ret = 0;
	ret = get_next_line(STDIN_FILENO, line);
	if (*line == NULL && ret < 1)
		return (0);
	if ((*data)->antbuf == NULL)
	{
		(*data)->antbuf = ft_strnew(ft_strlen(*line) + 1);
		if ((*data)->antbuf == NULL)
			memdel_error_exit(data, (void **)line, "Malloc failure");
		ft_strcpy((*data)->antbuf, *line);
		(*data)->antbuf[ft_strlen(*line)] = '\n';
		return (ret);
	}
	else
		return (append_line(line, data, ret));
}
