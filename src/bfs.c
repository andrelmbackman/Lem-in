/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 07:11:20 by leo               #+#    #+#             */
/*   Updated: 2022/11/19 19:24:04 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	reset_restricted(t_lemdata **data)
{
	t_room	*tmp;

	tmp = (*data)->rooms;
	while (tmp)
	{
		tmp->prev_path = -1;
		tmp->restricted = 0;
		tmp = tmp->next;
	}
	return (1);
}

static int	set_flows(t_lemdata **data, t_room *current)
{
	t_neighbor	*tmp;
	int			is_flow;

	is_flow = 0;
	tmp = get_aug_path((*data)->tmp_paths, current);
	while (tmp && tmp->index != (*data)->start->index)
	{
		if (tmp->prev \
			&& (*data)->pathtable[tmp->prev->index]->prev_path == tmp->index)
		{
			(*data)->pathtable[tmp->prev->index]->blocked = tmp->index;
			(*data)->pathtable[tmp->prev->index]->flow_id = (*data)->flow_id;
			is_flow = 1;
		}
		(*data)->pathtable[tmp->index]->restricted = (*data)->lvl;
		if (tmp->prev)
			(*data)->pathtable[tmp->index]->prev_path = tmp->prev->index;
		else
			(*data)->pathtable[tmp->index]->prev_path = (*data)->start->index;
		tmp = tmp->prev;
	}
	if (is_flow && reset_restricted(data))
		(*data)->flow_id++;
	return (1);
}

static int	store_condition(t_lemdata **data, t_room *next, t_room *current)
{
	if (next->blocked == current->index && (*data)->flow_id == 0)
		return (0);
	if (next->blocked == current->index && next->flow_id <= (*data)->flow_id \
		&& (*data)->flow_id != -1)
		return (0);
	if (next == (*data)->start)
		return (0);
	if (next->added == (*data)->lvl)
		return (0);
	if (next->restricted)
		return (0);
	if (current->restricted && next == (*data)->end)
		return (0);
	if (next->added < (*data)->lvl)
		return (1);
	return (0);
}

static int	flow_condition(t_lemdata **data, t_room *next, t_room *current)
{
	int	max_flow;

	max_flow = 7;
	if (next->blocked == current->index)
		return (0);
	if (current->restricted && !current->prev->restricted)
	{
		if (next->index != current->prev_path)
			return (0);
		return (1);
	}
	if (current->restricted && next == (*data)->end)
		return (0);
	if (next == (*data)->start \
		|| (current == (*data)->start && next->restricted))
		return (0);
	if (next->added < (*data)->lvl \
		&& next->prev_path != current->index && (*data)->flow_id < max_flow)
		return (1);
	return (0);
}

int	run_bfs(t_lemdata **data)
{
	int		path_len;

	init_tmp_paths(data);
	find_paths(data, &set_flows, &flow_condition);
	(path_len) = ++(*data)->flow_id;
	(*data)->paths = (t_path **)malloc(sizeof(t_path *) * path_len + 1);
	while (path_len-- > 0)
		(*data)->paths[path_len] = NULL;
	while ((*data)->flow_id-- > 0)
	{
		(*data)->lvl++;
		reset_restricted(data);
		find_paths(data, &store_path, &store_condition);
		(*data)->n_paths++;
	}
	return (1);
}
