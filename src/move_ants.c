/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 17:30:30 by abackman          #+#    #+#             */
/*   Updated: 2022/11/29 05:54:38 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	reverse_paths(t_path **pathset)
{
	t_path	*cur;
	t_path	*prev;
	t_path	*next;

	cur = *pathset;
	prev = NULL;
	next = NULL;
	while (cur)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*pathset = prev;
}

static int	max_steps(t_path *pathset)
{
	t_path	*tmp;
	int		max_steps;

	tmp = pathset;
	max_steps = 0;
	while (tmp)
	{
		if (tmp->steps == 1)
			return (1);
		if (tmp->n_ants && (tmp->n_ants + tmp->steps) > max_steps)
			max_steps = tmp->n_ants + tmp->steps;
		tmp = tmp->next;
	}
	return (max_steps);
}

static int	queue_to_paths(t_path *cur, int *ants_left)
{
	if (cur->next && cur->n_ants + cur->steps < \
	(cur->next->n_ants + cur->next->steps) && ants_left)
		return (1);
	else if (cur->next)
		return (0);
	return (1);
}

static int	queue_ants(t_lemdata **data, t_path	*pathset)
{
	t_path		*cur;
	int			ants_left;

	ants_left = (*data)->n_ants;
	(*data)->antqueue_total = (*data)->n_ants;
	if (pathset && pathset->next == NULL)
	{
		pathset->n_ants = ants_left;
		return (pathset->steps + pathset->n_ants);
	}
	cur = pathset;
	while (ants_left)
	{
		if (!pathset)
			break ;
		if (queue_to_paths(cur, &ants_left))
		{
			cur->n_ants++;
			cur = pathset;
			ants_left--;
		}
		else
			cur = cur->next;
	}
	return (max_steps(pathset));
}

int	move_ants(t_lemdata **data, int pathset)
{
	int		lowest;
	int		steps;
	int		i;

	lowest = 2147483647;
	steps = 2147483647;
	i = 0;
	while (i < (*data)->n_paths)
	{
		reverse_paths(&(*data)->paths[i]);
		steps = queue_ants(data, (*data)->paths[i]);
		if (steps < lowest)
		{
			lowest = steps;
			(*data)->chosen_path = i;
		}
		i++;
	}
	ft_putendl((*data)->antbuf);
	ft_strdel(&(*data)->antbuf);
	(*data)->antbuf = ft_strdup("");
	if (pathset >= 0 && pathset < (*data)->n_paths)
		(*data)->chosen_path = pathset;
	traverse_paths(data, (*data)->paths[(*data)->chosen_path]);
	return (0);
}
