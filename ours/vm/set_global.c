/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 21:31:47 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/22 16:36:54 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

int				create_player(char *file, t_global *global, int pid)
{
	int			fd;
	int			i;

	errno = 0;
	if ((fd = open((const char*)file, O_RDONLY)) == -1)
		return (open_err(errno));
	i = 0;
	while ((global->players)[i] != NULL)
		i++;
	(global->players)[i + 1] = NULL;
	if (((global->players)[i] = malloc(sizeof(t_player))) == NULL)
		return (malloc_err());
	((global->players)[i])->id = pid;
	if (!check_magic(fd) || !read_name(fd, (global->players)[i]) \
		|| !read_comment(fd, (global->players)[i]) \
		|| !read_code(fd, (global->players)[i]))
	{
		close(fd);
		return (0);
	}
	return (1);
}

int				get_players(int argc, char **argv, t_global *global)
{
	int			i;
	int			id;
	int			nb;

	i = 0;
	if (ft_streq(argv[1], "-dump") && (i = 2))
	{
		if (!isallnum(argv[2]))
			return (0);
		global->dump = ft_atoi(argv[2]);
	}
	nb = 0;
	while (++i < argc)
	{
		id = 0;
		if ((ft_streq(argv[i], "-n") && \
				(!ft_isallnum(argv[++i]) || !(id = ft_atoi(argv[i++])))) \
			|| ++nb > MAX_PLAYERS || !create_player(argv[i], global, id))
			return (0);
	}
	if (!sort_players((t_player**)(global->players)))
		return (0);
	return (1);
}

int				load_players(t_global *global)
{
	
}

int				set_global(int argc, char **argv, t_global *global)
{
	global->procs = NULL;
	(global->players)[0] = NULL;
	global->lives = 0;
	global->last = 0;
	global->ctd = CYCLE_TO_DIE;
	global->check = 0;
	global->dump = 0;
	global->show = 0;
	if (!(global->arena = malloc(MEM_SIZE)) /
		|| !get_players(argc, argv, global)\
		|| !load_players(global))
		return (0);
	return (1);
}
