/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leo <leo@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 13:34:30 by abackman          #+#    #+#             */
/*   Updated: 2022/11/29 07:00:56 by leo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "../libft/libft.h"
# include "node.h"
# define ERROR -1
# define START -42
# define END 42
# define INT_MAX 2147483647
# define MALLOCERROR "Malloc failure\n"

/*
** Struct to store neighboring rooms.
*/

typedef struct s_neighbor
{
	char				*name;
	int					index;
	int					path_id;
	struct s_neighbor	*next;
	struct s_neighbor	*prev;
}	t_neighbor;

/*
** Struct to represent a room and necessary data for that room.
*/

typedef struct s_stack
{
	t_node	*head;
	t_node	*tail;
}	t_stack;

typedef struct s_room
{
	struct s_room	*prev;
	struct s_room	*next;
	struct s_room	*hash_next;
	t_neighbor		*neighbors;
	char			*name;
	int				coord[2];
	int				index;
	int				n_neighbors;
	int				ant_id;
	int				path_id;
	int				blocked;
	int				flow_id;
	int				prev_path;
	int				restricted;
	int				added;
}	t_room;

/*
** Struct to save the possible paths from start to end.
*/

typedef struct s_path
{
	int				steps;
	int				n_ants;
	int				path_id;
	t_neighbor		*neighbors;
	t_neighbor		*tail;
	struct s_path	*next;
}	t_path;

/*
** Main struct with data about the map stored inside.
*/

typedef struct s_lemdata
{
	t_room	**hashtable;
	t_room	**pathtable;
	t_path	**paths;
	t_path	*tmp_paths;
	t_room	*rooms;
	t_room	*start;
	t_room	*end;
	t_stack	list;
	char	*antbuf;
	int		antqueue_total;
	int		n_rooms;
	int		n_ants;
	int		flow_id;
	int		n_paths;
	int		lvl;
	int		ants_at_sink;
	int		start_end;
	int		chosen_path;
	int		lines;
	int		lines_req;
}	t_lemdata;

/*
** Main functions used.
*/

int			read_input(t_lemdata **data);
int			find_paths(t_lemdata **data \
, int (*sink_next_fn)(t_lemdata **data, t_room *current) \
, int (*add)(t_lemdata **data, t_room *next, t_room *current));
int			move_ants(t_lemdata **data, int pathset);

/*
** Utilities/helper functions.
*/

t_neighbor	*get_aug_path(t_path *tmp_paths, t_room *current);
void		add_neighbor_tail(t_path *path);
void		init_data(t_lemdata *data);
void		init_room(t_room *room);
void		*free_structs(t_lemdata **data);
void		free_double_arrays(void **str, size_t n);
void		init_start_node(t_lemdata **data);
int			traverse_paths(t_lemdata **data, t_path *pathset);
int			traverse_path(t_lemdata **data, t_path *path);
int			read_input(t_lemdata **data);
int			add_link(t_lemdata **data, char *line);
int			add_room(t_room	**head, t_room *new, char **info, t_lemdata **data);
int			run_bfs(t_lemdata **data);
int			init_neighbor(t_neighbor **neighbor, char *name, int index);
int			init_pathtable(t_lemdata **data);
int			init_tmp_paths(t_lemdata **data);
int			store_path(t_lemdata **data, t_room *current);
int			init_path(t_path **path);
int			save_next_line(char **line, t_lemdata **data);
int			free_room_error(t_room *new, char **info);

/* 
** Bonus functions
*/

void		bonus_flags(t_lemdata data, int ac, char **av);
void		help_print(void);

/*
** Error functions
*/

void		error_exit(t_lemdata **data, char *text);
void		memdel_error_exit(t_lemdata **data, void **ptr, char *text);
void		arrdel_error_exit(t_lemdata **data, char **str, size_t n, \
char *text);

/* 
** Hash functions
*/

int			init_hash_table(t_lemdata **data);
t_room		*get_hashindex(t_lemdata **data, char *str);

#endif