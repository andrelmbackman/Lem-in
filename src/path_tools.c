/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 00:36:01 by leo               #+#    #+#             */
/*   Updated: 2022/11/23 16:59:51 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	direct_path(t_lemdata **data)
{
	int	i;

	i = 0;
	ft_putendl((*data)->antbuf);
	while (i++ < (*data)->n_ants)
	{
		ft_printf("L%d-%s", i, (*data)->end->name);
		if (i != (*data)->n_ants)
			ft_printf(" ");
	}
	ft_printf("\n");
	free_structs(data);
	exit(1);
}

int	init_pathtable(t_lemdata **data)
{
	t_room	**tmp_path;
	t_room	*tmp_room;
	int		i;

	tmp_room = (*data)->rooms;
	tmp_path = (t_room **)malloc((*data)->n_rooms * sizeof(t_room *));
	if (!tmp_path)
		return (0);
	(*data)->pathtable = tmp_path;
	i = 0;
	while (i < (*data)->n_rooms)
	{
		tmp_room->index = i;
		tmp_path[i++] = tmp_room;
		tmp_room = tmp_room->next;
	}
	return (1);
}

int	init_tmp_paths(t_lemdata **data)
{
	t_path		*tmp_path;
	t_path		*head;
	t_neighbor	*temp;
	int			i;

	i = 0;
	temp = (*data)->start->neighbors;
	if (!init_path(&tmp_path))
		error_exit(data, MALLOCERROR);
	head = tmp_path;
	while (temp)
	{
		if (temp->index == (*data)->end->index)
			direct_path(data);
		tmp_path->path_id = ++i;
		(*data)->pathtable[temp->index]->path_id = i;
		temp = temp->next;
		if (temp && !init_path(&tmp_path->next))
			error_exit(data, MALLOCERROR);
		tmp_path = tmp_path->next;
	}
	(*data)->tmp_paths = head;
	return (0);
}

t_neighbor	*get_aug_path(t_path *tmp_paths, t_room *current)
{
	t_path		*tmp_path;
	t_neighbor	*tmp_neighbor;

	tmp_path = tmp_paths;
	while (tmp_path && tmp_path->path_id != current->path_id)
		tmp_path = tmp_path->next;
	tmp_neighbor = tmp_path->neighbors;
	while (tmp_neighbor && tmp_neighbor->index != current->index)
		tmp_neighbor = tmp_neighbor->next;
	return (tmp_neighbor);
}

int	store_path(t_lemdata **data, t_room *current)
{
	t_room		*tmp_room;
	t_path		*tmp_path;
	t_neighbor	*new_neighbor;
	t_neighbor	*tmp;

	if (!init_path(&tmp_path))
		error_exit(data, MALLOCERROR);
	tmp_path->next = (*data)->paths[(*data)->flow_id];
	(*data)->paths[(*data)->flow_id] = tmp_path;
	tmp_room = (*data)->end;
	if (!init_neighbor(&tmp_path->neighbors, tmp_room->name, tmp_room->index))
		error_exit(data, MALLOCERROR);
	tmp = get_aug_path((*data)->tmp_paths, current);
	while (tmp && tmp->index != (*data)->start->index)
	{
		if (!init_neighbor(&new_neighbor, tmp->name, tmp->index))
			error_exit(data, MALLOCERROR);
		new_neighbor->next = tmp_path->neighbors;
		tmp_path->neighbors = new_neighbor;
		tmp_path->steps++;
		(*data)->pathtable[tmp->index]->restricted = tmp_path->steps;
		tmp = tmp->prev;
	}
	tmp_path->steps++;
	return (1);
}
