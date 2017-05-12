/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joeyplevy <joeyplevy@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/07 17:00:57 by joeyplevy         #+#    #+#             */
/*   Updated: 2017/05/11 15:52:42 by joeyplevy        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <corewar.h>

static void		ft_uputbinary(unsigned char *str, int size)
{
	int		i;
	char *strr;

	i = -1;
	strr = (char*)str;
	while (++i < size)
		printf("%02x ", strr[i] & 0xFF);
}

void		ft_putbinary(char *str, int size)
{
	int		i;

	i = -1;
	while (++i < size)
		ft_printf("%02x ", str[i] & 0xFF);
}

t_global	*init_global()
{
	t_global	*ret;
	int			i;

	if (!(ret = (t_global*)malloc(sizeof(t_global))))
		return (NULL);
	if (!(ret->arena = ft_memalloc(MEM_SIZE)))
		return (NULL);
	ret->procs = NULL;
	i = -1;
	while (++i < MAX_PLAYERS)
		if (!(ret->players[i] = (t_player*)malloc(sizeof(t_player))))
			return (NULL);
	ret->lives = 0;
	ret->last_id = 0;
	ret->ctd = CYCLE_TO_DIE;
	ret->checks = 0;
	ret->dump = -2;
	ret->show = 0;
	ret->nb_arg = 0;
	ret->nb_pl = 0;
	return (ret);
}

/*
static int 				get_poss(t_global *gb)
{
	int possition;

	possition = gb->nb_arg;
	//recuperation des possition
	return (possition);
}

static int				load_players(t_player *player)
{
	int i;
	int pos;

	i = 0;
	pos = get_poss(gb);
	ft_memcpy(gb->arena + pos, player->code, CHAMP_MAX_SIZE);
	ft_uputbinary(gb->arena, MEM_SIZE);
	return (1);
}

static void get_arg(int ac, char **av, t_global *gb)
{
	int i;

	i = 1;
	while (i != ac)
	{
		if (ft_strlen(av[i]) == 2)
			gb->nb_arg += 1;
		else
			gb->nb_player += 1;
		i++;
	}
	ft_printf("nb_player=%i\nnb_arg=%i\n", gb->nb_player, gb->nb_arg);
	if (gb->nb_arg > 0)
		;//a faire
}
*/

static int		check_double(t_player **players)
{
	int			i;
	int			j;

	i = -1;
	while (players[++i] != NULL)
	{
		j = i;
		while ((players[i])->id != 0 && players[++j] != NULL)
			if ((players[j])->id == (players[i])->id \
				|| (players[i])->id > MAX_PLAYERS)
				return (0);
	}
	return (1);
}

int				set_players_id(t_player **players)
{
	int			i;
	int			j;
	int			pid;

	if (!check_double(players))
		return (0);
	i = -1;
	pid = 1;
	while (players[++i] != NULL)
		if (!(players[i])->id)
		{
			j = -1;
			while (players[++j] != NULL)
				if (i != j && (players[j])->id == pid)
				{
					pid++;
					j = -1;
				}
			(players[i])->id = pid;
		}
	return (1);
}

int				get_player(t_global *global, int pid, t_parg arg)
{
	int			i;

	if (arg->fd <= 0)
		return(0);
	//	return(open_error(arg));
	while ((global->players)[i] != NULL)
		i++;
	(global->players)[i + 1] = NULL;
	if (((global->players)[i] = malloc(sizeof(t_player))) == NULL)
		return (malloc_err());
	((global->players)[i])->id = pid;
	if (!get_info_player(arg->fd, (global->players)[i]))
	{
		close(arg->fd);
		return (0);
	}
	close(arg->fd);
	return (1);
}

int			set_global(t_parg *args, t_global *global)
{
	t_arg	*a;

	a = args;
	while (tmp != NULL)
	{
		if (a->type == opt)
		{
			if (ft_streq(a->opt, "dump") && (a = a->next))
				gb->dump = a->val;
			else if (ft_streq(a->opt, "n"))
				gb->show = 1;
			else if (ft_strcmp(a->opt, "p") || ++(gb->nb_pl) > MAX_PLAYERS || \
						!get_player(gb, (a->next)->val, (a = (a->next)->next)))
				return (0);
		}
		else if (!get_player(gb, 0, a))
			return (0);
		a = a->next;
	}
	if (!set_players_id((t_players**)gb->players)) 
	//	|| !load_players(gb))
		return (0);
	return (1);
}

int			main(int ac, char **av)
{
	t_global	*global;
	t_parg		*args;
	int			fd;
	int 		i;

	i = 1;
	if (!(global = init_global()))
		return (0);
	ft_putendl("////init_global////");
	if (!(args = ft_get_args(ac, av, opt_tab, f)))
		return (0);
	ft_putendl("////ft_get_args////");
	if (!set_global(args, global))
		return (0);
	ft_putendl("////set_global////");
	while (i != global->nb_pl + 1)
	{
		ft_putbinary(global->players[i - 1]->name, PROG_NAME_LENGTH);
		ft_printf("\n\n");
		ft_putbinary(global->players[i - 1]->comment, COMMENT_LENGTH);
		ft_printf("\n\n");
		ft_putbinary(global->players[i - 1]->code, global->players[i - 1]->size);
		ft_printf("\n\n");
	}
	/*
	if (!(load_players(global)))
			ft_putendl("load_player");
	*/
	return (0);
}
