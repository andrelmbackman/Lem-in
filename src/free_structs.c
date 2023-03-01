/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 18:46:12 by abackman          #+#    #+#             */
/*   Updated: 2022/11/23 15:29:48 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	free_neighbors(t_neighbor *neighbor)
{
	t_neighbor	*current;
	t_neighbor	*next;

	current = neighbor;
	while (current)
	{
		next = current->next;
		ft_strdel(&current->name);
		ft_memdel((void **)&current);
		current = next;
	}
}

static void	free_rooms(t_room *rooms)
{
	t_room		*next;
	t_room		*current;

	current = rooms;
	while (current)
	{
		next = current->next;
		free_neighbors(current->neighbors);
		ft_strdel(&current->name);
		ft_memdel((void **)&current);
		current = next;
	}
}

static void	free_paths(t_path *path)
{
	t_path		*current;
	t_path		*next;

	current = path;
	while (current)
	{
		next = current->next;
		free_neighbors(current->neighbors);
		ft_memdel((void **)&current);
		current = next;
	}
}

void	*free_structs(t_lemdata **data)
{
	t_path	**tmp_path;
	t_path	*tmp;
	int		i;

	if (*data == NULL)
		return (NULL);
	tmp_path = (*data)->paths;
	i = 0;
	while (i < (*data)->n_paths && tmp_path && *tmp_path)
	{
		tmp = *tmp_path;
		free_paths(tmp);
		tmp_path++;
		i++;
	}
	ft_memdel((void **)&(*data)->paths);
	free_rooms((*data)->rooms);
	free_paths((*data)->tmp_paths);
	ft_strdel(&(*data)->antbuf);
	ft_memdel((void **)&(*data)->pathtable);
	ft_memdel((void **)&(*data)->hashtable);
	ft_memdel((void **)data);
	return (NULL);
}

void	free_double_arrays(void **arr, size_t n)
{
	if (arr)
	{
		while (n-- > 0)
		{
			if (arr[n])
				ft_memdel(&(arr[n]));
		}
		free(arr);
		arr = NULL;
	}
}
