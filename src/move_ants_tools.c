/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:15:26 by leo               #+#    #+#             */
/*   Updated: 2022/11/29 06:54:25 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_to_buf(t_lemdata **data, int id, char *name)
{
	char	*tmp;
	char	*new;

	tmp = NULL;
	new = NULL;
	ft_asprintf(&tmp, "L%d-%s ", id, name);
	if (!tmp)
		return (error_exit(data, "Printf error"));
	new = ft_strjoin((*data)->antbuf, tmp);
	if (!new)
		return (memdel_error_exit(data, (void **)&tmp, "Printf error"));
	ft_strdel(&(*data)->antbuf);
	ft_strdel(&tmp);
	(*data)->antbuf = new;
}

static void	move_ant(t_lemdata **data, t_path *path, t_room **cur, t_room **prv)
{
	if (*cur == (*data)->end && (*prv)->ant_id)
	{
		(*data)->ants_at_sink++;
		(*cur)->ant_id = (*prv)->ant_id;
		add_to_buf(data, (*cur)->ant_id, (*cur)->name);
	}
	if ((*prv)->ant_id)
	{
		(*cur)->ant_id = (*prv)->ant_id;
		(*prv)->ant_id = 0;
	}
	if ((*cur)->ant_id && *cur != (*data)->end)
		add_to_buf(data, (*cur)->ant_id, (*cur)->name);
	if (!ft_strcmp((*prv)->name, path->neighbors->name) && path->n_ants)
	{
		(*prv)->ant_id = (*data)->n_ants - (*data)->antqueue_total + 1;
		(*data)->antqueue_total--;
		path->n_ants--;
		add_to_buf(data, (*prv)->ant_id, (*prv)->name);
	}
}

int	traverse_path(t_lemdata **data, t_path *path)
{
	t_neighbor	*tmp;
	t_room		*tmproom;
	t_room		*tmproom_prev;

	add_neighbor_tail(&(*path));
	tmp = path->tail;
	while (tmp->prev)
	{
		tmproom = get_hashindex(data, tmp->name);
		tmproom_prev = get_hashindex(data, tmp->prev->name);
		move_ant(data, path, &tmproom, &tmproom_prev);
		tmp = tmp->prev;
	}
	return (0);
}

int	traverse_paths(t_lemdata **data, t_path *pathset)
{
	t_path		*tmp;

	while ((*data)->ants_at_sink < (*data)->n_ants)
	{
		tmp = pathset;
		while (tmp && (*data)->ants_at_sink != (*data)->n_ants)
		{
			traverse_path(data, tmp);
			tmp = tmp->next;
		}
		(*data)->antbuf[ft_strlen((*data)->antbuf) - 1] = '\n';
		(*data)->lines++;
	}
	ft_putstr((*data)->antbuf);
	return (0);
}
