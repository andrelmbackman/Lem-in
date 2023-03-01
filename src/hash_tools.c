/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 22:54:18 by leo               #+#    #+#             */
/*   Updated: 2022/11/10 23:01:37 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

/* hash * 33 + c */
static unsigned long	hash(char *str, int n_rooms)
{
	unsigned long	hash;
	unsigned long	i;

	hash = 5381;
	i = 0;
	while (str[i])
		hash = ((hash << 5) + hash) + str[i++];
	return (hash % n_rooms);
}

static void	add_to_hash_next(t_room	*head, t_room *new)
{
	t_room	*temp;

	temp = head;
	while (temp->hash_next)
		temp = temp->hash_next;
	temp->hash_next = new;
}

int	init_hash_table(t_lemdata **data)
{
	t_room	**hash_rooms;
	t_room	*temp;
	int		i;

	hash_rooms = (t_room **)malloc((*data)->n_rooms * sizeof(t_room *));
	if (!hash_rooms)
		return (0);
	temp = (*data)->rooms;
	i = 0;
	(*data)->hashtable = hash_rooms;
	while (i < (*data)->n_rooms)
		hash_rooms[i++] = NULL;
	while (temp)
	{
		i = hash(temp->name, (*data)->n_rooms);
		temp->index = i;
		if (hash_rooms[i] == NULL)
			hash_rooms[i] = temp;
		else
			add_to_hash_next(hash_rooms[i], temp);
		temp = temp->next;
	}
	return (1);
}

t_room	*get_hashindex(t_lemdata **data, char *str)
{
	t_room	*temp;
	int		index;

	index = hash(str, (*data)->n_rooms);
	temp = (*data)->hashtable[index];
	while (temp)
	{
		if (!ft_strcmp(str, temp->name))
			break ;
		temp = temp->hash_next;
	}
	return (temp);
}
