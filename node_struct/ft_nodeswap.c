/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeswap.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 15:13:55 by leotran           #+#    #+#             */
/*   Updated: 2022/09/22 12:38:01 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

void	ft_nodeswap(t_node **head)
{
	t_node	*node;

	node = (*head);
	(*head) = (*head)->next;
	node->next = (*head)->next;
	node->prev = (*head);
	(*head)->next = node;
	(*head)->prev = NULL;
}
