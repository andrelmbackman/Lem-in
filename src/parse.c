/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:34:30 by abackman          #+#    #+#             */
/*   Updated: 2022/11/29 14:45:02 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	parse_comment(t_lemdata **data, char *line)
{
	if ((*data)->start_end)
		memdel_error_exit(data, (void **)&line, "Error: no room after command");
	if (!ft_strcmp((const char *)line, "##start"))
		(*data)->start_end = START;
	else if (!ft_strcmp((const char *)line, "##end"))
		(*data)->start_end = END;
	else if (line[1] == '#')
		(*data)->start_end = 1;
	return (1);
}

static int	parse_ants(t_lemdata **data, char *line)
{
	long long	tmp;

	tmp = 0;
	save_next_line(&line, data);
	if (line == NULL)
		error_exit(data, "Input error");
	if (!ft_isstrdigit(line))
		memdel_error_exit(data, (void **)&line, "Ants error");
	tmp = ft_atoll((const char *)line);
	ft_strdel(&line);
	if (tmp < 1 || tmp > INT_MAX)
		error_exit(data, "Error: invalid ant number");
	(*data)->n_ants = (int)tmp;
	return (1);
}

static int	parse_room(t_lemdata **data, char *line)
{
	char	**info;
	t_room	*new;
	size_t	n;

	n = 0;
	if (line[0] == 'L')
		memdel_error_exit(data, (void **)&line, "Room name error");
	info = ft_strnsplit(line, ' ', &n);
	if (!info || n != 3)
		arrdel_error_exit(data, info, n, "Room format error");
	new = (t_room *)malloc(sizeof(t_room));
	if (new == NULL)
		error_exit(data, "Malloc failure");
	if (!add_room(&(*data)->rooms, new, info, data))
		memdel_error_exit(data, (void **)&line, "Room error");
	if ((*data)->start_end == START)
		(*data)->start = new;
	if ((*data)->start_end == END)
		(*data)->end = new;
	(*data)->start_end = 0;
	free_double_arrays((void **)info, n);
	return (1);
}

/*
** Parse the rest of the input, if !comment or !link, return error
*/

static int	parse_links(t_lemdata **data, char *line)
{
	size_t	bytes;
	int		ret;

	ret = 1;
	if (!(*data)->n_rooms)
		memdel_error_exit(data, (void **)&line, "Error: no rooms found");
	if (!init_hash_table(data) || !init_pathtable(data))
		memdel_error_exit(data, (void **)&line, MALLOCERROR);
	if (add_link(data, line) == ERROR)
		ret = ERROR;
	ft_strdel(&line);
	bytes = save_next_line(&line, data);
	while (bytes && ret)
	{
		if (line[0] == '#')
			parse_comment(data, line);
		else if (add_link(data, line) == ERROR)
			ret = ERROR;
		ft_strdel(&line);
		bytes = save_next_line(&line, data);
		(*data)->start_end = 0;
	}
	if (!(*data)->end || !(*data)->start)
		error_exit(data, "Error: no start/end room found");
	return (ret);
}

int	read_input(t_lemdata **data)
{
	char	*line;
	int		bytes;

	line = NULL;
	parse_ants(data, line);
	bytes = save_next_line(&line, data);
	while (bytes)
	{
		if (line[0] == '#')
			parse_comment(data, line);
		else if (ft_strchr(line, ' ') && parse_room(data, line))
			(*data)->n_rooms++;
		else if (ft_strchr(line, '-'))
			return (parse_links(data, line));
		ft_strdel(&line);
		bytes = save_next_line(&line, data);
	}
	error_exit(data, "Input error");
	return (1);
}
