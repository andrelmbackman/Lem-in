/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:34:30 by abackman          #+#    #+#             */
/*   Updated: 2022/11/29 06:48:18 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	check_duplicate_data(t_lemdata **data, t_room *cur)
{
	t_room	*tmp;

	tmp = cur->next;
	while (tmp)
	{
		if (!ft_strcmp(cur->name, tmp->name))
			error_exit(data, "Error: duplicate room name");
		if (cur->coord[0] == tmp->coord[0] && cur->coord[1] == tmp->coord[1])
			error_exit(data, "Error: duplicate coordinates");
		tmp = tmp->next;
	}
}

static void	check_data(t_lemdata **data)
{
	t_room	*tmp;

	tmp = (*data)->rooms;
	if (!(*data)->paths[0])
		error_exit(data, "Error: no solution found");
	if (!(*data)->start)
		error_exit(data, "No start room given");
	else if (!(*data)->end)
		error_exit(data, "No end room given");
	while (tmp && tmp->next != NULL)
	{
		check_duplicate_data(data, tmp);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av)
{
	t_lemdata	*data;
	int			i;

	i = -1;
	if (ac > 1 && !ft_strcmp(av[1], "-h"))
	{
		help_print();
		return (1);
	}
	data = (t_lemdata *)malloc(sizeof(t_lemdata));
	if (data == NULL)
		error_exit(NULL, MALLOCERROR);
	init_data(data);
	if (read_input(&data) == ERROR)
		error_exit(&data, "Input error");
	run_bfs(&data);
	check_data(&data);
	move_ants(&data, i);
	if (ac > 2 && ft_strequ(av[ac - 2], "-set") && ft_isstrdigit(av[ac - 1]))
		i = ft_atoi(av[ac - 1]);
	if (ac > 1)
		bonus_flags(*data, ac, av);
	free_structs(&data);
	return (0);
}
