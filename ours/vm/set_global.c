/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/20 21:31:47 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/04/25 23:25:25 by joeyplevy        ###   ########.fr       */
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
	if (!get_player_info(fd, (global->players)[i]))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int				get_players(int argc, char **argv, t_global *global)
{
	int			i;
	int			id;
	int			nb;

	i = 0;
	if (ft_streq(argv[1], "-dump") && (i = 2))
		if (!isallnum(argv[2]) || !(global->dump = ft_atoi(argv[2])))
			return (0);
	nb = 0;
	while (++i < argc)
	{
		id = 0;
		if ((ft_streq(argv[i], "-n") && (++i) + 1 < argc && \
				(!ft_isallnum(argv[i]) || !(id = ft_atoi(argv[i++])))) \
			|| ++nb > MAX_PLAYERS || !create_player(argv[i], global, id))
			return (0);
	}
	if (!sort_players((t_player**)(global->players)))
		return (0);
	return (1);
}

int				init_arena(t_global *global)
{
	int			i;

	if ((global->arena = (unsigned char*)malloc(MEM_SIZE)) == NULL)
		return (0);
	i = -1;
	while (++i < MEM_SIZE)
		(global->arena)[i] = 0;
	return (1);
}

t_global			*init_global(int argc, char **argv)
{
	t_global		*ret;

	if ((ret = (t_global*)malloc(sizeof(t_global))) == NULL)
		return (NULL);
	ret->procs = NULL;
	(ret->players)[0] = NULL;
	ret->lives = 0;
	ret->last_id = 0;
	ret->ctd = CYCLE_TO_DIE;
	ret->checks = 0;
	ret->dump = -2;
	ret->show = 0;
	if (!init_arena(ret) /
		|| !get_players(argc, argv, ret)\
		|| !load_players(ret))
		return (0);
	return (1);
}
