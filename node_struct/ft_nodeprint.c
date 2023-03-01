/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nodeprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 03:12:42 by leo               #+#    #+#             */
/*   Updated: 2022/10/15 22:51:08 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "node.h"
#include "../libft/ft_printf/includes/ft_printf.h"

void	ft_nodeprint(t_node **head)
{
	t_node	*current;

	current = *head;
	while (current)
	{
		ft_printf("%d ", current->num);
		current = current->next;
	}
	ft_printf("\n");
}
