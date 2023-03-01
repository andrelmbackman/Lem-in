/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:13:17 by abackman          #+#    #+#             */
/*   Updated: 2022/11/19 19:09:17 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	add_to_queue(t_stack *list, int hash_index)
{
	t_node	*temp;

	temp = ft_nodenew(hash_index);
	if (!temp)
		return ;
	ft_nodeadd_end(&list->tail, temp);
}

static int	add_to_tmp_path(t_lemdata **data, t_room *current, t_room *next)
{
	t_neighbor	*tmp_neighbor;
	t_neighbor	*new;
	t_path		*tmp_path;

	if (!init_neighbor(&new, next->name, next->index))
		error_exit(data, MALLOCERROR);
	if (current == (*data)->start)
		current->path_id = next->path_id;
	tmp_path = (*data)->tmp_paths;
	while (tmp_path && tmp_path->path_id != current->path_id)
		tmp_path = tmp_path->next;
	new->next = tmp_path->neighbors;
	new->path_id = current->path_id;
	tmp_neighbor = new;
	while (tmp_neighbor && tmp_neighbor->index != current->index)
		tmp_neighbor = tmp_neighbor->next;
	new->prev = tmp_neighbor;
	tmp_path->neighbors = new;
	next->path_id = current->path_id;
	return (1);
}

static int	iterate_neighbors(t_lemdata **data, t_room *current \
	, int (*sink_next_fn)(t_lemdata **data, t_room *current) \
	, int (*add_check)(t_lemdata **data, t_room *next, t_room *current))
{
	t_neighbor	*tmp_neighbor;
	t_room		*next;

	tmp_neighbor = current->neighbors;
	while (tmp_neighbor)
	{
		next = (*data)->pathtable[tmp_neighbor->index];
		if (!current->restricted && next == (*data)->end)
		{
			next->prev = current;
			return (sink_next_fn(data, current));
		}
		if (add_check(data, next, current))
		{
			add_to_tmp_path(data, current, next);
			next->prev = current;
			next->added = (*data)->lvl;
			add_to_queue(&(*data)->list, tmp_neighbor->index);
		}
		tmp_neighbor = tmp_neighbor->next;
	}
	return (0);
}

int	find_paths(t_lemdata **data \
	, int (*sink_next_fn)(t_lemdata **data, t_room *current) \
	, int (*add_check)(t_lemdata **data, t_room *next, t_room *current))
{
	t_room	*current;
	t_node	*tmp_node;
	t_node	*old_node;

	tmp_node = ft_nodenew((*data)->start->index);
	(*data)->list.tail = tmp_node;
	while (tmp_node)
	{
		current = (*data)->pathtable[tmp_node->num];
		if (iterate_neighbors(data, current, sink_next_fn, add_check))
		{
			ft_nodedel(&tmp_node);
			tmp_node = ft_nodenew((*data)->start->index);
			(*data)->list.tail = tmp_node;
			(*data)->lvl++;
			continue ;
		}
		old_node = tmp_node;
		tmp_node = tmp_node->next;
		ft_memdel((void **)&old_node);
	}
	return (0);
}
