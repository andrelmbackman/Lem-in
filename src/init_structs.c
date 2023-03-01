/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 13:38:27 by abackman          #+#    #+#             */
/*   Updated: 2022/11/29 06:03:39 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_data(t_lemdata *data)
{
	data->hashtable = NULL;
	data->pathtable = NULL;
	data->paths = NULL;
	data->rooms = NULL;
	data->start = NULL;
	data->end = NULL;
	data->tmp_paths = NULL;
	data->list.head = NULL;
	data->list.tail = NULL;
	data->flow_id = 1;
	data->lvl = 1;
	data->antqueue_total = 0;
	data->antbuf = NULL;
	data->n_rooms = 0;
	data->n_paths = 0;
	data->n_ants = 0;
	data->ants_at_sink = 0;
	data->start_end = 0;
	data->lines = 0;
	data->lines_req = 0;
	data->chosen_path = -1;
}

void	init_room(t_room *room)
{
	room->name = NULL;
	room->neighbors = NULL;
	room->next = NULL;
	room->prev = NULL;
	room->hash_next = NULL;
	room->n_neighbors = 0;
	room->ant_id = 0;
	room->restricted = 0;
	room->added = 0;
	room->flow_id = 0;
	room->prev_path = -1;
	room->path_id = -1;
	room->coord[0] = -1;
	room->coord[1] = -1;
	room->index = -1;
	room->blocked = -1;
}

int	init_path(t_path **path)
{
	*path = (t_path *)malloc(sizeof(t_path));
	if (!(*path))
		return (0);
	(*path)->neighbors = NULL;
	(*path)->tail = NULL;
	(*path)->next = NULL;
	(*path)->steps = 0;
	(*path)->n_ants = 0;
	(*path)->path_id = 0;
	return (1);
}

int	init_neighbor(t_neighbor **neighbor, char *name, int index)
{
	*neighbor = (t_neighbor *)malloc(sizeof(t_neighbor));
	if (!(*neighbor))
		return (0);
	(*neighbor)->name = ft_strdup(name);
	if (!(*neighbor)->name)
	{
		ft_memdel((void **)neighbor);
		return (0);
	}
	(*neighbor)->index = index;
	(*neighbor)->next = NULL;
	(*neighbor)->prev = NULL;
	return (1);
}

void	init_start_node(t_lemdata **data)
{
	t_node	*tmp_node;

	if (!(*data)->list.head)
	{
		(*data)->list.head = ft_nodenew((*data)->start->index);
		if (!(*data)->list.head)
			error_exit(data, MALLOCERROR);
		(*data)->list.tail = (*data)->list.head;
	}
	else
	{
		tmp_node = ft_nodepop(&(*data)->list.head);
		ft_nodedel(&(*data)->list.head);
		(*data)->list.head = tmp_node;
		(*data)->list.tail = (*data)->list.head;
	}
}
