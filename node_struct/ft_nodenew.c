/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:50:05 by leotran           #+#    #+#             */
/*   Updated: 2022/10/17 11:14:16 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node	*ft_nodenew(int n)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node)
	{
		node->num = n;
		node->next = NULL;
		node->prev = NULL;
	}
	return (node);
}
