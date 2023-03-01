/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:29:58 by leo               #+#    #+#             */
/*   Updated: 2022/11/29 06:51:07 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	print_chosen_path(t_lemdata data)
{
	t_path		*tmp;
	t_neighbor	*tmp_neighbor;
	int			i;

	tmp = data.paths[data.chosen_path];
	i = 0;
	ft_printf("Chosen pathset:\n[PATHSET %d]", data.chosen_path);
	while (tmp)
	{
		tmp_neighbor = tmp->neighbors;
		ft_printf("\n  Path %d: ", i++);
		while (tmp_neighbor)
		{
			ft_printf("{%s}", tmp_neighbor->name);
			tmp_neighbor = tmp_neighbor->next;
		}
		tmp = tmp->next;
	}
}

static void	print_path(t_lemdata data)
{
	t_path		*tmp_path;
	t_neighbor	*tmp_neighbor;
	int			i;

	i = 0;
	if (!data.paths)
		return ;
	while (i < data.n_paths)
	{
		ft_printf("\n[PATHSET %d]\n", i);
		tmp_path = data.paths[i++];
		while (tmp_path)
		{
			ft_printf("	");
			ft_printf("steps: %-2d ", tmp_path->steps);
			tmp_neighbor = tmp_path->neighbors;
			while (tmp_neighbor)
			{
				ft_printf("{%s}", tmp_neighbor->name);
				tmp_neighbor = tmp_neighbor->next;
			}
			ft_printf("\n");
			tmp_path = tmp_path->next;
		}
	}
}

static void	custom_pathset(t_lemdata data, char *av)
{
	int	i;

	i = ft_atoi(av);
	if (i < 0 || i >= data.n_paths || !ft_isstrdigit(av))
	{
		ft_printf("Invalid pathset!\n");
		ft_printf("Default pathset[%d] chosen.\n", data.chosen_path);
		ft_printf("Available pathsets: [0-%d]\n", data.n_paths - 1);
	}
	else
		ft_printf("Custom pathset given: [%s]", av);
}

void	help_print(void)
{
	ft_printf("Available flags:\n");
	ft_printf(" [-v]: Print all paths found.\n");
	ft_printf(" [-p]: Print chosen path.\n");
	ft_printf(" [-l]: Print number of lines.\n");
	ft_printf(" [-x]: Check for memory leaks.\n");
	ft_printf(" [-set n]: Specify custom pathset, n is an unsigned int\n");
	ft_printf(" [!] -set flag must be used last following an unsigned int\n");
	ft_printf(" [-h]: Print help options.\n");
}

void	bonus_flags(t_lemdata data, int ac, char **av)
{
	int		i;

	i = 0;
	ft_printf("\n");
	while (i++ < ac - 1)
	{
		if (ft_strequ(av[i], "-v"))
			print_path(data);
		else if (ft_strequ(av[i], "-p"))
			print_chosen_path(data);
		else if (ft_strequ(av[i], "-l"))
			ft_printf("#Lines required: %d\n#Lines printed: %d\n" \
			, data.lines_req, data.lines);
		else if (ft_strequ(av[i], "-x"))
			system("leaks -q lem-in");
		else if (ft_strequ(av[i], "-set") && i == ac - 2)
			custom_pathset(data, av[++i]);
		else if (ft_strequ(av[i], "-h"))
			help_print();
		else
		{
			ft_printf("\nInvalid flag.\n");
			help_print();
		}
	}
}
