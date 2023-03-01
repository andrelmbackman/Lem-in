/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abackman <abackman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:34:30 by abackman          #+#    #+#             */
/*   Updated: 2022/11/23 18:57:44 by abackman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	free_room_error(t_room *new, char **info)
{
	free_double_arrays((void **)info, 3);
	ft_memdel((void **)&new);
	return (0);
}

void	error_exit(t_lemdata **data, char *text)
{
	ft_putendl_fd(text, STDERR_FILENO);
	free_structs(data);
	exit(1);
}

void	memdel_error_exit(t_lemdata **data, void **ptr, char *text)
{
	ft_putendl_fd(text, STDERR_FILENO);
	ft_memdel((void **)ptr);
	free_structs(data);
	exit(1);
}

void	arrdel_error_exit(t_lemdata **data, char **str, size_t n, char *text)
{
	ft_putendl_fd(text, STDERR_FILENO);
	free_double_arrays((void **)str, n);
	free_structs(data);
	exit(1);
}
