/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodepop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:02:12 by leotran           #+#    #+#             */
/*   Updated: 2022/09/12 22:39:24 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"

t_node	*ft_nodepop(t_node **node)
{
	t_node	*temp;

	temp = (*node);
	(*node) = (*node)->next;
	temp->prev = NULL;
	temp->next = NULL;
	return (temp);
}
