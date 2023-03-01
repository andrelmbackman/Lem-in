/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 21:22:41 by leo               #+#    #+#             */
/*   Updated: 2022/11/29 13:20:05 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	add_neighbor_to_hash(t_lemdata **data, t_room *hash_room \
	, char *name, int index)
{
	t_neighbor	*neighbor;
	t_neighbor	*tmp;

	if (!init_neighbor(&neighbor, name, index))
		error_exit(data, MALLOCERROR);
	hash_room->n_neighbors++;
	tmp = hash_room->neighbors;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = neighbor;
	}
	else
		hash_room->neighbors = neighbor;
	return (1);
}

static int	check_link_names(t_lemdata **data, t_room **head \
	, t_room **link, char *line)
{
	int	len;
	len = ft_strlen(line);
	while (len-- > 0)
	{
		if (line[len] == '-')
			*link = get_hashindex(data, &line[len + 1]);
		if (*link)
			break ;
	}
	if (len == 0 && !(*link))
		return (ERROR);
	line[len] = '\0';
	*head = get_hashindex(data, line);
	return (1);
}

/*
** Checks parsing for a link between rooms, stores this data if successful
*/

int	add_link(t_lemdata **data, char *line)
{
	t_room	*head;
	t_room	*link;
	int		ret;

	ret = 1;
	head = NULL;
	link = NULL;
	ret = check_link_names(data, &head, &link, line);
	if (!head || !link)
		memdel_error_exit(data, (void **)&line, "Link error");
	if (add_neighbor_to_hash(data, head, link->name, link->index))
		ret = add_neighbor_to_hash(data, link, head->name, head->index);
	return (ret);
}

/*
** Adds a pointer to the last node of t_path to the tail pointer
*/

void	add_neighbor_tail(t_path *path)
{
	t_path		*tmpath;
	t_neighbor	*tmp;

	tmpath = path;
	while (tmpath)
	{
		tmp = tmpath->neighbors;
		while (tmp)
		{
			tmp->next->prev = tmp;
			tmp = tmp->next;
			if (tmp && !tmp->next)
			{
				tmpath->tail = tmp;
				break ;
			}
		}
		tmpath = tmpath->next;
	}
}

/*
** Checks that the parsing for the room is successful, stores the new room data
*/

int	add_room(t_room	**head, t_room *new, char **info, t_lemdata **data)
{
	t_room		*tmp;

	tmp = *head;
	init_room(new);
	if (!ft_isstrdigit(info[1]) || !ft_isstrdigit(info[2]))
		return (free_room_error(new, info));
	new->name = ft_strdup(info[0]);
	if (!new->name)
		return (free_room_error(new, info));
	new->index = (*data)->n_rooms;
	if (ft_atoll(info[1]) > INT_MAX || ft_atoll(info[2]) > INT_MAX \
		|| ft_atoll(info[1]) < 0 || ft_atoll(info[2]) < 0)
		arrdel_error_exit(data, info, 3, "Error: invalid coordinates");
	new->coord[0] = ft_atoi(info[1]);
	new->coord[1] = ft_atoi(info[2]);
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (1);
}
