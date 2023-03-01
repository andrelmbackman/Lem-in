/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leotran <leotran@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:18:45 by leotran           #+#    #+#             */
/*   Updated: 2022/09/23 10:37:51 by leotran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	ft_nodeadd_front(t_node **head, t_node *node)
{
	node->next = (*head);
	node->prev = NULL;
	(*head)->prev = node;
	(*head) = node;
}
